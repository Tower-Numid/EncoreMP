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

            mEnchanter.getClass().skillUsageSucceeded (mEnchanter, ESM::Skill::Enchant, 2);
        }

        enchantment.mEffects = mEffectList;

        int count = getEnchantItemsCount();

        if(mCastStyle==ESM::Enchantment::ConstantEffect)
            enchantment.mData.mCharge = 0;
        else
            enchantment.mData.mCharge = getGemCharge() / count;

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

    /*
     * Vanilla enchant cost formula:
     *
     *  Touch/Self:          (min + max) * baseCost * 0.025 * duration + area * baseCost * 0.025
     *  Target:       1.5 * ((min + max) * baseCost * 0.025 * duration + area * baseCost * 0.025)
     *  Constant eff:        (min + max) * baseCost * 2.5              + area * baseCost * 0.025
     *
     *  For multiple effects - cost of each effect is multiplied by number of effects that follows +1.
     *
     *  Note: Minimal value inside formula for 'min' and 'max' is 1. So in vanilla:
     *        (0 + 0) == (1 + 0) == (1 + 1) => 2 or (2 + 0) == (1 + 2) => 3
     *
     *  Formula on UESPWiki is not entirely correct.
     */
    float Enchanting::getEnchantPoints(bool precise) const
    {
        if (mEffectList.mList.empty())
            // No effects added, cost = 0
            return 0;

        const MWWorld::ESMStore &store = MWBase::Environment::get().getWorld()->getStore();
        const float fEffectCostMult = store.get<ESM::GameSetting>().find("fEffectCostMult")->mValue.getFloat();
        const float fEnchantmentConstantDurationMult = store.get<ESM::GameSetting>().find("fEnchantmentConstantDurationMult")->mValue.getFloat();

        float enchantmentCost = 0.f;
        float cost = 0.f;
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

            cost += ((magMin + magMax) * duration + area) * baseCost * fEffectCostMult * 0.05f;

            cost = std::max(1.f, cost);

            if (effect.mRange == ESM::RT_Target)
                cost *= 1.5f;

            if (mCastStyle == ESM::Enchantment::WhenStrikes)
                cost *= 2;

			if (magicEffect)
			{
				int school = magicEffect->mData.mSchool;
				if (school == 2 || school == 5)
				{
					cost *= 2;
				}
                if (effenumid == 57 || effenumid == 74 || effenumid == 86 || effenumid == 88 || effenumid == 99)
                {
                    cost *= 2;
                }
                if (effenumid == 79)
                {
                    cost *= 0.5;
                }
                if (mCastStyle == ESM::Enchantment::ConstantEffect)
                {
                    if (effenumid == 3 || effenumid == 40 || effenumid == 42 || effenumid == 77 || effenumid == 79 || effenumid == 99)
                    {
                        cost *= 1.5;
                    }
                }
                if (mCastStyle == ESM::Enchantment::CastOnce)
                {
                    if (school == 0 || school == 1)
                    {
                        cost *= 0.5;
                    }
                }
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

        float priceMultipler = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find ("fEnchantmentValueMult")->mValue.getFloat();
        int price = MWBase::Environment::get().getMechanicsManager()->getBarterOffer(mEnchanter, static_cast<int>(getEnchantPoints() * priceMultipler), true);
        const float enchantpointforcost = getEnchantPoints();
        price *= getEnchantItemsCount() * getTypeMultiplier();

        if (mCastStyle == ESM::Enchantment::ConstantEffect)
        {
            price += 70000;
            if (enchantpointforcost > 30)
            {
                float CEexceeds30 = (enchantpointforcost - 30);
                int CEexceeds30cost = static_cast<int>(CEexceeds30 * priceMultipler * 3);
                price += CEexceeds30cost;
                if (enchantpointforcost > 90)
                {
                    float CEexceeds90 = (enchantpointforcost - 90);
                    int CEexceeds90cost = static_cast<int>(CEexceeds90 * priceMultipler * 7);
                    price += CEexceeds90cost;
                    if (enchantpointforcost > 100)
                    {
                        price += 5000000;
                    }
                }
            }
        }

        if (mCastStyle == ESM::Enchantment::WhenStrikes)
        {
            price += 5000;
            if (enchantpointforcost > 5)
            {
                float exceeds5 = (enchantpointforcost - 5);
                int exceeds5cost = static_cast<int>(exceeds5 * priceMultipler * 2);
                price += exceeds5cost;
                if (enchantpointforcost > 10)
                {
                    float exceeds10 = (enchantpointforcost - 10);
                    int exceeds10cost = static_cast<int>(exceeds10 * priceMultipler);
                    price += exceeds10cost;
                    if (enchantpointforcost > 15)
                    {
                        float exceeds15 = (enchantpointforcost - 15);
                        int exceeds15cost = static_cast<int>(exceeds15 * priceMultipler * 5);
                        price += exceeds15cost;
                        if (enchantpointforcost > 20)
                        {
                            float exceeds20 = (enchantpointforcost - 20);
                            int exceeds20cost = static_cast<int>(exceeds20 * priceMultipler * 30);
                            price += exceeds20cost;
                            if (enchantpointforcost > 25)
                            {
                                price += 5000000;
                            }
                        }
                    }
                }
            }
        }

        if (mCastStyle == ESM::Enchantment::WhenUsed)
        {
            price += 5000;
            if (enchantpointforcost > 5)
            {
                float exceeds5 = (enchantpointforcost - 5);
                int exceeds5cost = static_cast<int>(exceeds5 * priceMultipler);
                price += exceeds5cost;
                if (enchantpointforcost > 10)
                {
                    float exceeds10 = (enchantpointforcost - 10);
                    int exceeds10cost = static_cast<int>(exceeds10 * priceMultipler);
                    price += exceeds10cost;
                    if (enchantpointforcost > 15)
                    {
                        float exceeds15 = (enchantpointforcost - 15);
                        int exceeds15cost = static_cast<int>(exceeds15 * priceMultipler * 2.5);
                        price += exceeds15cost;
                        if (enchantpointforcost > 20)
                        {
                            float exceeds20 = (enchantpointforcost - 20);
                            int exceeds20cost = static_cast<int>(exceeds20 * priceMultipler * 15);
                            price += exceeds20cost;
                            if (enchantpointforcost > 25)
                            {
                                price += 5000000;
                            }
                        }
                    }
                }
            }
        }

        if (mCastStyle == ESM::Enchantment::CastOnce)
        {
            price = static_cast<int>(price * 0.2);
            if (enchantpointforcost > 20)
            {
                float exceeds20 = (enchantpointforcost - 20);
                int exceeds20cost = static_cast<int>(exceeds20 * priceMultipler * 1.2);
                price += exceeds20cost;
                if (enchantpointforcost > 25)
                {
                    float exceeds25 = (enchantpointforcost - 25);
                    int exceeds25cost = static_cast<int>(exceeds25 * priceMultipler * 10);
                    price += exceeds25cost;
                    if (enchantpointforcost > 30)
                    {
                        price += 5000000;
                    }
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
        const float enchantpointsforpenalty = getEnchantPoints();

        float x = (a - getEnchantPoints() * fEnchantmentChanceMult * getTypeMultiplier() * getEnchantItemsCount() + 0.2f * b + 0.1f * c) * stats.getFatigueTerm();

        const MWWorld::Ptr ptrPlayer = MWBase::Environment::get().getWorld()->getPlayerPtr();
        const MWMechanics::NpcStats &ptrNpcStats = ptrPlayer.getClass().getNpcStats(ptrPlayer);
        const int baseenchantforCE = ptrNpcStats.getSkill(9).getBase();

        if (mCastStyle == ESM::Enchantment::ConstantEffect)
        {
            if (baseenchantforCE < 75 || a < 75)
            {
                x = 0;
            }
            else if (baseenchantforCE >= 100 && a >= 100)
            {
                x = 100;
            }
            else if (baseenchantforCE >= 95 && a >= 95 && enchantpointsforpenalty <= 90)
            {
                x = 100;
            }
            else if (baseenchantforCE >= 90 && a >= 90 && enchantpointsforpenalty <= 75)
            {
                x = 100;
            }
            else if (baseenchantforCE >= 85 && a >= 85 && enchantpointsforpenalty <= 60)
            {
                x = 100;
            }
            else if (baseenchantforCE >= 80 && a >= 80 && enchantpointsforpenalty <= 45)
            {
                x = 100;
            }
            else if (baseenchantforCE >= 75 && a >= 75 && enchantpointsforpenalty <= 30)
            {
                x = 100;
            }
        }

        if (mCastStyle == ESM::Enchantment::WhenUsed || mCastStyle == ESM::Enchantment::WhenStrikes)
        {
            if (enchantpointsforpenalty < 5.1)
            {
                x += 25;
            }
            if (enchantpointsforpenalty > 20.1)
            {
                float enchantpenaltyA = enchantpointsforpenalty - 20;
                x -= (10 * enchantpenaltyA);
            }
            if (enchantpointsforpenalty > 25.1)
            {
                float enchantpenaltyB = enchantpointsforpenalty - 25;
                x -= (10 * enchantpenaltyB);
            }
        }


        if (mCastStyle == ESM::Enchantment::CastOnce)
        {
            x += 25;
            if (enchantpointsforpenalty < 5.1)
            {
                x += 25;
            }
            if (enchantpointsforpenalty > 20.1)
            {
                float enchantpenaltyA = enchantpointsforpenalty - 20;
                x -= (10 * enchantpenaltyA);
            }
            if (enchantpointsforpenalty > 25.1)
            {
                float enchantpenaltyB = enchantpointsforpenalty - 25;
                x -= (10 * enchantpenaltyB);
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
                static const float multiplier = std::max(0.f, std::min(1.0f, Settings::Manager::getFloat("projectiles enchant multiplier", "Game")));
                MWWorld::Ptr player = getPlayer();
                int itemsInInventoryCount = player.getClass().getContainerStore(player).count(mOldItemPtr.getCellRef().getRefId());
                count = std::min(itemsInInventoryCount, std::max(1, 20));
            }
        }

        return count;
    }

    float Enchanting::getTypeMultiplier() const
    {
        static const bool useMultiplier = Settings::Manager::getFloat("projectiles enchant multiplier", "Game") > 0;
        if (useMultiplier && mWeaponType != -1 && getEnchantPoints() > 0)
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
