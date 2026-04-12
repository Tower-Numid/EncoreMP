#include <cmath>

#include "enchanting.hpp"

#include <components/misc/rng.hpp>
#include <components/settings/settings.hpp>

/*
    Start of tes3mp addition

    Include additional headers for multiplayer purposes
*/
#include <components/openmw-mp/TimedLog.hpp>
#include "../mwmp/Main.hpp"
#include "../mwmp/Networking.hpp"
#include "../mwmp/LocalPlayer.hpp"
#include "../mwmp/Worldstate.hpp"
/*
    End of tes3mp addition
*/

#include "../mwworld/manualref.hpp"
#include "../mwworld/class.hpp"
#include "../mwworld/containerstore.hpp"
#include "../mwworld/esmstore.hpp"


#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"
#include "../mwbase/mechanicsmanager.hpp"


#include "creaturestats.hpp"
#include "spellutil.hpp"
#include "actorutil.hpp"
#include "weapontype.hpp"


#include "mechanicsmanagerimp.hpp"
#include "../mwclass/creature.hpp"
#include "../mwworld/player.hpp"

namespace MWMechanics
{
    Enchanting::Enchanting()
        : mCastStyle(ESM::Enchantment::CastOnce)
        , mSelfEnchanting(false)
        , mWeaponType(-1)
    {}

    void Enchanting::setOldItem(const MWWorld::Ptr& oldItem)
    {
        mOldItemPtr=oldItem;
        mWeaponType = -1;
        mObjectType.clear();
        if(!itemEmpty())
        {
            mObjectType = mOldItemPtr.getTypeName();
            if (mObjectType == typeid(ESM::Weapon).name())
                mWeaponType = mOldItemPtr.get<ESM::Weapon>()->mBase->mData.mType;
        }
    }

    void Enchanting::setNewItemName(const std::string& s)
    {
        mNewItemName=s;
    }

    void Enchanting::setEffect(const ESM::EffectList& effectList)
    {
        mEffectList=effectList;
    }

    int Enchanting::getCastStyle() const
    {
        return mCastStyle;
    }

    void Enchanting::setSoulGem(const MWWorld::Ptr& soulGem)
    {
        mSoulGemPtr=soulGem;
    }

    bool Enchanting::create()
    {
        const MWWorld::Ptr& player = getPlayer();
        MWWorld::ContainerStore& store = player.getClass().getContainerStore(player);
        ESM::Enchantment enchantment;
        enchantment.mData.mFlags = 0;
        enchantment.mData.mType = mCastStyle;
        enchantment.mData.mCost = getBaseCastCost();

        store.remove(mSoulGemPtr, 1, player);

        //Exception for Azura Star, new one will be added after enchanting
        if(Misc::StringUtils::ciEqual(mSoulGemPtr.get<ESM::Miscellaneous>()->mBase->mId, "Misc_SoulGem_Azura"))
            store.add("Misc_SoulGem_Azura", 1, player);

        if(mSelfEnchanting)
        {
            if(getEnchantChance() <= (Misc::Rng::roll0to99()))
                return false;

            //EncoreMP block start to introduce variable XP based on soul size

            float enchantXpMod = 1.0f;
            float enchantXpMod2 = 0.0f;
            int soulSize = getGemCharge();

            if (soulSize <= 0)
            {
                enchantXpMod = 1.0f;
            }
            else if (soulSize >= 400)
            {
                enchantXpMod = 4.0f;
            }
            else if (soulSize >= 180)
            {
                enchantXpMod = 3.0f;
                enchantXpMod2 = (soulSize - 180);
                enchantXpMod2 *= (1.0f / 220.0f);
                enchantXpMod += enchantXpMod2;
            }
            else if (soulSize >= 60)
            {
                enchantXpMod = 2.0f;
                enchantXpMod2 = (soulSize - 60);
                enchantXpMod2 *= (1.0f / 120.0f);
                enchantXpMod += enchantXpMod2;
            }
            else
            {
                enchantXpMod = 1.0f;
                enchantXpMod2 = soulSize;
                enchantXpMod2 *= (1.0f / 60.0f);
                enchantXpMod += enchantXpMod2;
            }

            //EncoreMP block end to introduce variable XP based on soul size


            mEnchanter.getClass().skillUsageSucceeded (mEnchanter, ESM::Skill::Enchant, 2, enchantXpMod);
        }

        enchantment.mEffects = mEffectList;

        int count = getEnchantItemsCount();

        if(mCastStyle==ESM::Enchantment::ConstantEffect)
            enchantment.mData.mCharge = 0;
        else
            enchantment.mData.mCharge = getGemCharge();

        // Try to find a dynamic enchantment with the same stats, create a new one if not found.
        const ESM::Enchantment* enchantmentPtr = getRecord(enchantment);
        if (enchantmentPtr == nullptr)
            enchantmentPtr = MWBase::Environment::get().getWorld()->createRecord (enchantment);

        // Apply the enchantment

        /*
            Start of tes3mp change (major)

            Send the enchantment's record to the server

            Don't add the new item to the player's inventory and instead expect the server to
            add it

            Store the quantity used for the enchantment so it can be retrieved in applyEnchantment()
            when applicable
            
            The applyEnchantment() method is where the record of the newly enchanted item will be sent
            to the server, causing the server to send back the player's inventory with the new item
            included
        */
        mwmp::Main::get().getNetworking()->getWorldstate()->sendEnchantmentRecord(enchantmentPtr);

        store.remove(mOldItemPtr, count, player);

        if(!mSelfEnchanting)
            payForEnchantment();

        mwmp::Main::get().getLocalPlayer()->storeLastEnchantmentQuantity(count);

        std::string newItemId = mOldItemPtr.getClass().applyEnchantment(mOldItemPtr, enchantmentPtr->mId, getGemCharge(), mNewItemName);
        /*
            End of tes3mp change (major)
        */

        return true;
    }
    
    void Enchanting::nextCastStyle()
    {
        if (itemEmpty())
            return;

        const bool powerfulSoul = getGemCharge() >= \
                MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find ("iSoulAmountForConstantEffect")->mValue.getInteger();
        if ((mObjectType == typeid(ESM::Armor).name()) || (mObjectType == typeid(ESM::Clothing).name()))
        { // Armor or Clothing
            switch(mCastStyle)
            {
                case ESM::Enchantment::WhenUsed:
                    if (powerfulSoul)
                        mCastStyle = ESM::Enchantment::ConstantEffect;
                    return;
                default: // takes care of Constant effect too
                    mCastStyle = ESM::Enchantment::WhenUsed;
                    return;
            }
        }
        else if (mWeaponType != -1)
        { // Weapon
            ESM::WeaponType::Class weapclass = MWMechanics::getWeaponType(mWeaponType)->mWeaponClass;
            switch(mCastStyle)
            {
                case ESM::Enchantment::WhenStrikes:
                    if (weapclass == ESM::WeaponType::Melee || weapclass == ESM::WeaponType::Ranged)
                        mCastStyle = ESM::Enchantment::WhenUsed;
                    return;
                case ESM::Enchantment::WhenUsed:
                    if (powerfulSoul && weapclass != ESM::WeaponType::Ammo && weapclass != ESM::WeaponType::Thrown)
                        mCastStyle = ESM::Enchantment::ConstantEffect;
                    else if (weapclass != ESM::WeaponType::Ranged)
                        mCastStyle = ESM::Enchantment::WhenStrikes;
                    return;
                default: // takes care of Constant effect too
                    mCastStyle = ESM::Enchantment::WhenUsed;
                    if (weapclass != ESM::WeaponType::Ranged)
                        mCastStyle = ESM::Enchantment::WhenStrikes;
                    return;
            }
        }
        else if(mObjectType == typeid(ESM::Book).name())
        { // Scroll or Book
            mCastStyle = ESM::Enchantment::CastOnce;
            return;
        }

        // Fail case
        mCastStyle = ESM::Enchantment::CastOnce;
    }

    float Enchanting::getEnchantPoints(bool precise) const
    {
        if (mEffectList.mList.empty())
            // No effects added, cost = 0
            return 0;

        const MWWorld::ESMStore &store = MWBase::Environment::get().getWorld()->getStore();
        const float fEffectCostMult = store.get<ESM::GameSetting>().find("fEffectCostMult")->mValue.getFloat();
        const float fEnchantmentConstantDurationMult = store.get<ESM::GameSetting>().find("fEnchantmentConstantDurationMult")->mValue.getFloat();

        float enchantmentCost = 0.f;

        for (const ESM::ENAMstruct& effect : mEffectList.mList)
        {
            float baseCost = (store.get<ESM::MagicEffect>().find(effect.mEffectID))->mData.mBaseCost;
            int effenumid = effect.mEffectID;
            int magMin = std::max(1, effect.mMagnMin);
            int magMax = std::max(1, effect.mMagnMax);
            int area = std::max(1, effect.mArea);
            float duration = static_cast<float>(effect.mDuration);
			const auto magicEffect = MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find(effect.mEffectID);


            if (mCastStyle == ESM::Enchantment::ConstantEffect)
                duration = fEnchantmentConstantDurationMult;

            float rawcost = ((magMin + magMax) * duration + area) * baseCost * fEffectCostMult * 0.05f;

            float multpool = 1.0f;

            //cost += ((magMin + magMax) * duration + area) * baseCost * fEffectCostMult * 0.05f;

            //cost = std::max(1.f, cost);


            // EncoreMP, various changes to how specific effects are handled

            if (effect.mRange == ESM::RT_Target)
                multpool *= 1.5f;


            // EncoreMP, double the cost of all on-strike enchantments for balance reasons
            if (mCastStyle == ESM::Enchantment::WhenStrikes)
                multpool *= 2.0f;



			if (magicEffect)
			{
				int school = magicEffect->mData.mSchool;
                // EncoreMP, double the cost of all destruction and restoration enchants of any kind, for balance (stacks with on-strike mod)
				if (school == 2 || school == 5)
				{
                    multpool *= 2.0f;
				}
                if (effenumid == 86 || effenumid == 88)
                {
                    //EncoreMP, also double the cost of absorb health/fatigue when enchanting, as they are the only other sources of direct damage not in destruction
                    multpool *= 2.0f;
                }
			}

            float extra = std::max(0.0f, rawcost - 1.0f);
            float cost = 1.0f + extra * multpool;

            //EncoreMP V0.92, halve all enchantment costs on scrolls
            if (mCastStyle == ESM::Enchantment::CastOnce)
            {
                cost *= 0.5f;
            }

            enchantmentCost += precise ? cost : std::floor(cost);


        }

        return enchantmentCost;
    }

    const ESM::Enchantment* Enchanting::getRecord(const ESM::Enchantment& toFind) const
    {
        const MWWorld::Store<ESM::Enchantment>& enchantments = MWBase::Environment::get().getWorld()->getStore().get<ESM::Enchantment>();
        MWWorld::Store<ESM::Enchantment>::iterator iter (enchantments.begin());
        iter += (enchantments.getSize() - enchantments.getDynamicSize());
        for (; iter != enchantments.end(); ++iter)
        {
            if (iter->mEffects.mList.size() != toFind.mEffects.mList.size())
                continue;

            if (iter->mData.mFlags != toFind.mData.mFlags
                    || iter->mData.mType != toFind.mData.mType
                    || iter->mData.mCost != toFind.mData.mCost
                    || iter->mData.mCharge != toFind.mData.mCharge)
                continue;

            // Don't choose an ID that came from the content files, would have unintended side effects
            if (!enchantments.isDynamic(iter->mId))
                continue;

            bool mismatch = false;

            for (int i=0; i<static_cast<int> (iter->mEffects.mList.size()); ++i)
            {
                const ESM::ENAMstruct& first = iter->mEffects.mList[i];
                const ESM::ENAMstruct& second = toFind.mEffects.mList[i];

                if (first.mEffectID!=second.mEffectID ||
                    first.mArea!=second.mArea ||
                    first.mRange!=second.mRange ||
                    first.mSkill!=second.mSkill ||
                    first.mAttribute!=second.mAttribute ||
                    first.mMagnMin!=second.mMagnMin ||
                    first.mMagnMax!=second.mMagnMax ||
                    first.mDuration!=second.mDuration)
                {
                    mismatch = true;
                    break;
                }
            }

            if (!mismatch)
                return &(*iter);
        }

        return nullptr;
    }

    int Enchanting::getBaseCastCost() const
    {
        if (mCastStyle == ESM::Enchantment::ConstantEffect)
            return 0;

        return static_cast<int>(getEnchantPoints(false));
    }

    int Enchanting::getEffectiveCastCost() const
    {
        int baseCost = getBaseCastCost();
        MWWorld::Ptr player = getPlayer();
        if (getCastStyle() == ESM::Enchantment::WhenStrikes)
            baseCost *= 0.25;
        return getEffectiveEnchantmentCastCost(static_cast<float>(baseCost), player);
    }


    int Enchanting::getEnchantPrice() const
    {
        if(mEnchanter.isEmpty())
            return 0;

        // Encore, get enchantment points to allow cost modification
        float enchantpointforcost = getEnchantPoints();

        // Encore, apply a cost increase past 30 points, to mirror the new difficulty logic
        if (mCastStyle == ESM::Enchantment::WhenUsed || mCastStyle == ESM::Enchantment::CastOnce || mCastStyle == ESM::Enchantment::WhenStrikes)
        {
            if (enchantpointforcost > 30.0f)
            {
                enchantpointforcost = (30.0f + ((enchantpointforcost - 30.0f)*1.5f));
            }
        }

        // base game logic to calculate price, using enchantpointforcost now instead of getEnchantPoints()
        float priceMultipler = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find("fEnchantmentValueMult")->mValue.getFloat();
        int price = MWBase::Environment::get().getMechanicsManager()->getBarterOffer(mEnchanter, static_cast<int>(enchantpointforcost * priceMultipler), true);
        price *= getEnchantItemsCount() * getTypeMultiplier();

        // Encore, double the price for constant effects
        if (mCastStyle == ESM::Enchantment::ConstantEffect)
        {
            price *= 2;
        }

        // Encore, lower scroll costs to 1/25th
        if (mCastStyle == ESM::Enchantment::CastOnce)
        {
            price *= 0.04;
        }

        ESM::WeaponType::Class weapClass = MWMechanics::getWeaponType(mWeaponType)->mWeaponClass;

        //Encore, lower ammunition costs to 1/20th
        if (mCastStyle == ESM::Enchantment::WhenStrikes)
        {
            if (mWeaponType != -1)
            {
                if (weapClass == ESM::WeaponType::Thrown || weapClass == ESM::WeaponType::Ammo)
                {
                    price *= 0.05;
                }
            }
        }

        return std::max(1, price);
    }

    int Enchanting::getGemCharge() const
    {
        const MWWorld::ESMStore &store = MWBase::Environment::get().getWorld()->getStore();
        if(soulEmpty())
            return 0;
        if(mSoulGemPtr.getCellRef().getSoul()=="")
            return 0;
        const ESM::Creature* soul = store.get<ESM::Creature>().search(mSoulGemPtr.getCellRef().getSoul());
        if(soul)
            return soul->mData.mSoul;
        else
            return 0;
    }

    int Enchanting::getMaxEnchantValue() const
    {
        if (itemEmpty())
            return 0;

        const MWWorld::ESMStore &store = MWBase::Environment::get().getWorld()->getStore();

        float enchantmentCapacity = mOldItemPtr.getClass().getEnchantmentPoints(mOldItemPtr);
        if (enchantmentCapacity + 5 < 0) {
            return 0;
        }
        else {
            return static_cast<int>(std::sqrt((enchantmentCapacity/10) + 5) * 100 * store.get<ESM::GameSetting>().find("fEnchantmentMult")->mValue.getFloat());
        }
    }

    bool Enchanting::soulEmpty() const
    {
        return mSoulGemPtr.isEmpty();
    }

    bool Enchanting::itemEmpty() const
    {
        return mOldItemPtr.isEmpty();
    }

    void Enchanting::setSelfEnchanting(bool selfEnchanting)
    {
        mSelfEnchanting = selfEnchanting;
    }

    void Enchanting::setEnchanter(const MWWorld::Ptr& enchanter)
    {
        mEnchanter = enchanter;
        // Reset cast style
        mCastStyle = ESM::Enchantment::CastOnce;
    }

    int Enchanting::getEnchantChance() const
    {
        const CreatureStats& stats = mEnchanter.getClass().getCreatureStats(mEnchanter);
        const MWWorld::Store<ESM::GameSetting>& gmst = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>();
        const float a = static_cast<float>(mEnchanter.getClass().getSkill(mEnchanter, ESM::Skill::Enchant));
        const float b = static_cast<float>(stats.getAttribute (ESM::Attribute::Intelligence).getModified());
        const float c = static_cast<float>(stats.getAttribute (ESM::Attribute::Luck).getModified());
        const float fEnchantmentChanceMult = gmst.find("fEnchantmentChanceMult")->mValue.getFloat();
        const float fEnchantmentConstantChanceMult = gmst.find("fEnchantmentConstantChanceMult")->mValue.getFloat();
        const float enchantPointsForCE = getEnchantPoints();
        float enchantPointsHolder = getEnchantPoints();
        float d = 0.0f;

        ESM::WeaponType::Class weapclass = MWMechanics::getWeaponType(mWeaponType)->mWeaponClass;

        //soul size to success rate modifier
        int soulSize = getGemCharge();
        float enchantDifficultyMod = 0.0f;
        float enchantDifficultyMod2 = 0.0f;

        if (soulSize <= 0)
        {
            enchantDifficultyMod = 0.0f;
        }
        else if (soulSize >= 400)
        {
            enchantDifficultyMod = 30.0f;
        }
        else if (soulSize >= 180)
        {
            enchantDifficultyMod = 30.0f;
            enchantDifficultyMod2 = (soulSize - 180);
            enchantDifficultyMod2 *= (10.0f / 220.0f);
            enchantDifficultyMod += enchantDifficultyMod2;
        }
        else if (soulSize >= 120)
        {
            enchantDifficultyMod = 15.0f;
            enchantDifficultyMod2 = (soulSize - 120);
            enchantDifficultyMod2 *= (5.0f / 60.0f);
            enchantDifficultyMod += enchantDifficultyMod2;
        }
        else if (soulSize >= 60)
        {
            enchantDifficultyMod = 10.0f;
            enchantDifficultyMod2 = (soulSize - 60);
            enchantDifficultyMod2 *= (5.0f / 60.0f);
            enchantDifficultyMod += enchantDifficultyMod2;
        }
        else if (soulSize >= 30)
        {
            enchantDifficultyMod = 5.0f;
            enchantDifficultyMod2 = (soulSize - 30);
            enchantDifficultyMod2 *= (5.0f / 30.0f);
            enchantDifficultyMod += enchantDifficultyMod2;
        }
        else
        {
            enchantDifficultyMod = 0.0f;
            enchantDifficultyMod2 = soulSize;
            enchantDifficultyMod2 *= (5.0f / 30.0f);
            enchantDifficultyMod += enchantDifficultyMod2;
        }

        //when used logic + cast once (scroll) logic + on-strike logic
        //comes before the float x = equation so that this value is modified by fatigue, GMST, etc

        if (mCastStyle == ESM::Enchantment::WhenUsed || mCastStyle == ESM::Enchantment::CastOnce || mCastStyle == ESM::Enchantment::WhenStrikes)
        {
            //small boost to generic success to smooth low levels
            d += 5;
            //add soul gem size bonus to success rate
            d += enchantDifficultyMod;
            //add a large boost for scrolls with costs less than 10
            if (mCastStyle == ESM::Enchantment::CastOnce)
            {
                if (enchantPointsHolder < 10)
                {
                    d += 40;
                    d -= (enchantPointsHolder * 4);
                }
            }
            // increase difficulty when enchanting capacity exceeds 30
            // for every point over 30, add half its value again to the cost
            if (enchantPointsHolder > 30)
            {
                float enchantPenaltyB = enchantPointsHolder - 30;
                enchantPenaltyB *= 0.5;
                enchantPointsHolder += enchantPenaltyB;
            }
        }

        //Encore addition, account for enchanting less than 20 ammunition at a time
        float typeMult = 1.0f;
        const int itemCount = getEnchantItemsCount();

        if (mWeaponType != -1)
        {
            //modify the per ammo difficulty to normalise it for all amounts of ammo
            if (weapclass == ESM::WeaponType::Thrown || weapclass == ESM::WeaponType::Ammo)
            {
                typeMult = (1.0f / itemCount);
                //add the same success rate for 10 and below that scrolls get, to make throwing weapons/ammo easier at low levels
                if (enchantPointsHolder < 10)
                {
                    d += 40;
                    d -= (enchantPointsHolder * 4);
                }
            }
        }

        //get new constant effect logic server setting, true = use EncoreMP, false = revert to base game behaviour
        bool useEncoreConstantEffectLogic = Settings::Manager::getBool("use new constant effect difficulty logic", "Game");

        float x = ((a + d) - enchantPointsHolder * fEnchantmentChanceMult * typeMult * itemCount + 0.2f * b + 0.1f * c) * stats.getFatigueTerm();

        const MWWorld::Ptr ptrPlayer = MWBase::Environment::get().getWorld()->getPlayerPtr();
        const MWMechanics::NpcStats &ptrNpcStats = ptrPlayer.getClass().getNpcStats(ptrPlayer);
        const float baseEnchantForCE = ptrNpcStats.getSkill(9).getBase();
        const float modifiedEnchantForCE = static_cast<float>(mEnchanter.getClass().getSkill(mEnchanter, ESM::Skill::Enchant));


        // CE logic, operates independently of all other enchanting difficulty checks
        // Looks for player base skill and enchantment size to determine difficulty
        // enchantPointsForCE = size of the enchantment (float)
        // baseEnchantForCE = players base enchanting skill (float)
        // modifiedEnchantForCE = modified skill (float)

        // get the lowest of base and modified skill, so that skill drain/damage is accounted for, but buffs to the skill are not
        float skillForCE = std::min(baseEnchantForCE, modifiedEnchantForCE);
        float allowedEnchantSize = 0.0f;
        float skillOverHolder = 0.0f;


        if (mCastStyle == ESM::Enchantment::ConstantEffect)
        {
            if (useEncoreConstantEffectLogic == true)
            {
                if (skillForCE < 60.0f)
                {
                    //always fail is skill is below 60
                    x = 0;
                }
                else if (skillForCE >= 100.0f)
                {
                    //always succed when skill is 100
                    x = 100;
                }
                else
                {
                    // calculate the allowed size you can make based on skill

                    if (skillForCE < 70.0f)
                    {
                        allowedEnchantSize = 5.0f;
                        skillOverHolder = (skillForCE - 60.0f);
                        allowedEnchantSize += skillOverHolder;
                    }
                    else if (skillForCE < 80.0f)
                    {
                        allowedEnchantSize = 15.0f;
                        skillOverHolder = (skillForCE - 70.0f);
                        allowedEnchantSize += (2.0f * skillOverHolder);
                    }
                    else if (skillForCE < 90.0f)
                    {
                        allowedEnchantSize = 35.0f;
                        skillOverHolder = (skillForCE - 80.0f);
                        allowedEnchantSize += (3.0f * skillOverHolder);
                    }
                    else
                    {
                        allowedEnchantSize = 65.0f;
                        skillOverHolder = (skillForCE - 90.0f);
                        allowedEnchantSize += (4.0f * skillOverHolder);
                    }

                    //if allowed size is equal to or greater than the size you are trying to make, always suceed, else always fail
                    if (allowedEnchantSize >= enchantPointsForCE)
                    {
                        x = 100;
                    }
                    else
                    {
                        x = 0;
                    }
                }
            }
            else
            {
                x *= fEnchantmentConstantChanceMult;
            }
        }

        return static_cast<int>(x);
    }

    int Enchanting::getEnchantItemsCount() const
    {
        int count = 1;
        float enchantPoints = getEnchantPoints();
        if (mWeaponType != -1 && enchantPoints > 0)
        {
            ESM::WeaponType::Class weapclass = MWMechanics::getWeaponType(mWeaponType)->mWeaponClass;
            if (weapclass == ESM::WeaponType::Thrown || weapclass == ESM::WeaponType::Ammo)
            {
                //static const float multiplier = std::max(0.f, std::min(1.0f, Settings::Manager::getFloat("projectiles enchant multiplier", "Game")));
                //disabled for EncoreMP V0.92
                MWWorld::Ptr player = getPlayer();
                int itemsInInventoryCount = player.getClass().getContainerStore(player).count(mOldItemPtr.getCellRef().getRefId());
                count = std::min(itemsInInventoryCount, std::max(1, 20));
            }
        }

        return count;
    }

    float Enchanting::getTypeMultiplier() const
    {
        //static const bool useMultiplier = Settings::Manager::getFloat("projectiles enchant multiplier", "Game") > 0;
        //disabled for EncoreMP V0.92
        if (mWeaponType != -1 && getEnchantPoints() > 0)
        {
            ESM::WeaponType::Class weapclass = MWMechanics::getWeaponType(mWeaponType)->mWeaponClass;
            if (weapclass == ESM::WeaponType::Thrown || weapclass == ESM::WeaponType::Ammo)
                return 0.05f;
        }

        return 1.f;
    }

    void Enchanting::payForEnchantment() const
    {
        const MWWorld::Ptr& player = getPlayer();
        MWWorld::ContainerStore& store = player.getClass().getContainerStore(player);

        store.remove(MWWorld::ContainerStore::sGoldId, getEnchantPrice(), player);

        // add gold to NPC trading gold pool
        CreatureStats& enchanterStats = mEnchanter.getClass().getCreatureStats(mEnchanter);
        enchanterStats.setGoldPool(enchanterStats.getGoldPool() + getEnchantPrice());
    }
}
