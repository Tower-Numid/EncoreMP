#include "alchemy.hpp"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <stdexcept>
#include <map>

#include <components/misc/rng.hpp>

#include <components/esm/loadskil.hpp>
#include <components/esm/loadappa.hpp>
#include <components/esm/loadgmst.hpp>
#include <components/esm/loadmgef.hpp>

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

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"

#include "../mwworld/esmstore.hpp"
#include "../mwworld/containerstore.hpp"
#include "../mwworld/class.hpp"
#include "../mwworld/cellstore.hpp"

#include "magiceffects.hpp"
#include "creaturestats.hpp"

MWMechanics::Alchemy::Alchemy()
    : mValue(0)
    , mPotionName("")
{
}

std::set<MWMechanics::EffectKey> MWMechanics::Alchemy::listEffects() const
{
    std::map<EffectKey, int> effects;

    for (TIngredientsIterator iter(mIngredients.begin()); iter != mIngredients.end(); ++iter)
    {
        if (!iter->isEmpty())
        {
            const MWWorld::LiveCellRef<ESM::Ingredient> *ingredient = iter->get<ESM::Ingredient>();

            std::set<EffectKey> seenEffects;

            for (int i = 0; i < 4; ++i)
                if (ingredient->mBase->mData.mEffectID[i] != -1)
                {
                    EffectKey key(
                        ingredient->mBase->mData.mEffectID[i], ingredient->mBase->mData.mSkills[i] != -1 ?
                        ingredient->mBase->mData.mSkills[i] : ingredient->mBase->mData.mAttributes[i]);

                    if (seenEffects.insert(key).second)
                        ++effects[key];
                }
        }
    }

    std::set<EffectKey> effects2;

    for (std::map<EffectKey, int>::const_iterator iter(effects.begin()); iter != effects.end(); ++iter)
        if (iter->second > 1)
            effects2.insert(iter->first);

    return effects2;
}

void MWMechanics::Alchemy::applyTools(int flags, float& value) const
{
    //bool magnitude = !(flags & ESM::MagicEffect::NoMagnitude);
    //bool duration = !(flags & ESM::MagicEffect::NoDuration);
    bool negative = (flags & ESM::MagicEffect::Harmful) != 0;

    if (!mTools[ESM::Apparatus::Calcinator].isEmpty())
    {
        float calcinatorQuality = mTools[ESM::Apparatus::Calcinator].get<ESM::Apparatus>()->mBase->mData.mQuality;
        if (negative == true)
        {
            calcinatorQuality /= (10.0f / 3.0f);
            calcinatorQuality += 1.0f;
            value *= calcinatorQuality;
        }
        else
        {
            calcinatorQuality /= 10.0f;
            calcinatorQuality += 1.0f;
            value *= calcinatorQuality;
        }
    }

    if (!mTools[ESM::Apparatus::Alembic].isEmpty())
    {
        if (negative == true)
        {
            float alembicQuality = mTools[ESM::Apparatus::Alembic].get<ESM::Apparatus>()->mBase->mData.mQuality;
            float alembicMod = (0.4f * alembicQuality);
            alembicMod = (1.0f - alembicMod);
            alembicMod = std::max(0.1f, alembicMod);
            value *= alembicMod;
        }
    }

    if (!mTools[ESM::Apparatus::Retort].isEmpty())
    {
        if (negative == true)
        {
            value = value;
        }
        else
        {
            float retortQuality = mTools[ESM::Apparatus::Retort].get<ESM::Apparatus>()->mBase->mData.mQuality;
            retortQuality /= 10.0f;
            retortQuality += 1.0f;
            value *= retortQuality;
        }
    }
}

void MWMechanics::Alchemy::updateEffects()
{
    mEffects.clear();
    mValue = 0;

    if (countIngredients()<2 || mAlchemist.isEmpty() || mTools[ESM::Apparatus::MortarPestle].isEmpty())
        return;

    //dwemer coda, ingredient value logic
    int numberIngredients = countIngredients();

    std::vector<int> ingredientValues;


    for (TIngredientsIterator it = beginIngredients(); it != endIngredients(); ++it)
    {
        if (it->isEmpty()) continue;

        auto *wrap = it->get<ESM::Ingredient>();
        if (!wrap) continue;

        auto *base = wrap->mBase;
        if (!base) continue;

        int value = base->mData.mValue;

        ingredientValues.push_back(value);
    }
    // iterate over ingredients, guarding, get ID, add their value to the vector

    int sumIngredientValue = 0;
    for (int v : ingredientValues) sumIngredientValue += v;
    // add them all up into sumIngredientValue as an int

    //dwemer coda end

    // find effects
    std::set<EffectKey> effects (listEffects());

    // general alchemy factor
    float x = getAlchemyFactor();

    float averageIngredientValue = 0.0f;
    float priceMod = 0.0f;
    float multMod = 1.0f;
    
    //average the ingredient values with guarding against 0s
    //then work out benefit from tiers and apply, dwemer coda
    if ((sumIngredientValue > 0) && (numberIngredients > 0))
    {
        averageIngredientValue = (sumIngredientValue / numberIngredients);

        if (averageIngredientValue < 5.0f)
        {
            multMod = 0.7f;
        }
        else if ((averageIngredientValue >= 5.0f) && (averageIngredientValue < 200.0f))
        {
            // y = 64.46238 + (-293895.7 - 64.46238)/(1 + (x/3.767532e-32)^0.116272)
            // where y is skill boost, and x is ingredient value

            float yf = 64.5f + (-293960.0f / (1.0f + std::powf(averageIngredientValue / 3.76e-32f, 0.11627f)));
            priceMod += yf;
        }
        else if (averageIngredientValue >= 200.0f)
        {
            priceMod = 30.0f;
            float highValueHolder = (averageIngredientValue - 200.0f);
            highValueHolder /= 10.0f;
            priceMod += highValueHolder;
        }

        if (averageIngredientValue >= 100.0f)
        {
            multMod = 1.1f;
        }
    }

    if (sumIngredientValue == 0.0f)
    {
        multMod = 0.7f;
    }

    x += priceMod;
    x *= multMod;

    // begin step down mortar effectiveness, dwemer coda
    float mortarQuality = mTools[ESM::Apparatus::MortarPestle].get<ESM::Apparatus>()->mBase->mData.mQuality;

    float mortarModifier = 1.0f;
    float qHolder = 1.0f;

    if (mortarQuality < 1.0f)
    {
        qHolder = (1.0f - mortarQuality);
        qHolder /= 2.0f;
        qHolder = (1.0f - qHolder);
        mortarModifier = qHolder;
    }

    if (mortarQuality > 1.0f)
    {
        qHolder = (mortarQuality - 1.0f);
        qHolder /= 2.0f;
        qHolder += 1.0f;
        mortarModifier = qHolder;
    }

    x *= mortarModifier;

    // end step down mortar effectiveness, dwemer coda

    x *= MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find ("fPotionStrengthMult")->mValue.getFloat();


    // potion value, with dwemer coda cap added
    mValue = static_cast<int> (
        x * MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find ("iAlchemyMod")->mValue.getFloat());
    mValue = std::min(mValue, sumIngredientValue);

    // dwemer coda convert alchemyfactor to magicka budget

    float potionMagickaBudget = (x / 6.0f);


    // build quantified effect list
    for (std::set<EffectKey>::const_iterator iter (effects.begin()); iter!=effects.end(); ++iter)
    {
        const ESM::MagicEffect *magicEffect =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find (iter->mId);

        if (magicEffect->mData.mBaseCost<=0)
        {
            const std::string os = "invalid base cost for magic effect " + std::to_string(iter->mId);
            throw std::runtime_error (os);
        }

        float fPotionT1MagMul =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find ("fPotionT1MagMult")->mValue.getFloat();

        if (fPotionT1MagMul<=0)
            throw std::runtime_error ("invalid gmst: fPotionT1MagMul");

        float fPotionT1DurMult =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find ("fPotionT1DurMult")->mValue.getFloat();

        if (fPotionT1DurMult<=0)
            throw std::runtime_error ("invalid gmst: fPotionT1DurMult");

        // dwemer coda budget to effect converter start

        float vHolderOne = (potionMagickaBudget / magicEffect->mData.mBaseCost);
        vHolderOne *= 40.0f;
        float durHolder = sqrtf(vHolderOne);
        float magHolder = (durHolder / 2.0f);

        //override duration to budget over two, if the effect has no magnitude
        if (magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude)
        {
            durHolder = (vHolderOne / 2.0f);
        }

        //override magnitude to budget over two, if the effect has no duration
        if (magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration)
        {
            magHolder = (vHolderOne / 4.0f);
        }

        // dwemer coda budget to effect converter end

        float magnitude = (magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude) ?
            1.0f : magHolder;
        float duration = (magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration) ?
            1.0f : durHolder;

        if (!(magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude))
            applyTools (magicEffect->mData.mFlags, magnitude);

        if (!(magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration))
            applyTools (magicEffect->mData.mFlags, duration);

        duration *= fPotionT1DurMult;
        magnitude *= fPotionT1MagMul;

        duration = roundf(duration);
        magnitude = roundf(magnitude);

        if (magnitude>0 && duration>0)
        {
            ESM::ENAMstruct effect;
            effect.mEffectID = iter->mId;

            effect.mAttribute = -1;
            effect.mSkill = -1;

            if (magicEffect->mData.mFlags & ESM::MagicEffect::TargetSkill)
                effect.mSkill = iter->mArg;
            else if (magicEffect->mData.mFlags & ESM::MagicEffect::TargetAttribute)
                effect.mAttribute = iter->mArg;

            effect.mRange = 0;
            effect.mArea = 0;

            effect.mDuration = static_cast<int>(duration);
            effect.mMagnMin = effect.mMagnMax = static_cast<int>(magnitude);

            mEffects.push_back (effect);
        }
    }
}

const ESM::Potion *MWMechanics::Alchemy::getRecord(const ESM::Potion& toFind) const
{
    const MWWorld::Store<ESM::Potion> &potions =
        MWBase::Environment::get().getWorld()->getStore().get<ESM::Potion>();

    MWWorld::Store<ESM::Potion>::iterator iter = potions.begin();
    for (; iter != potions.end(); ++iter)
    {
        if (iter->mEffects.mList.size() != mEffects.size())
            continue;

        if (iter->mName != toFind.mName
                || iter->mScript != toFind.mScript
                || iter->mData.mWeight != toFind.mData.mWeight
                || iter->mData.mValue != toFind.mData.mValue
                || iter->mData.mAutoCalc != toFind.mData.mAutoCalc)
            continue;

        // Don't choose an ID that came from the content files, would have unintended side effects
        // where alchemy can be used to produce quest-relevant items
        if (!potions.isDynamic(iter->mId))
            continue;

        bool mismatch = false;

        for (int i=0; i<static_cast<int> (iter->mEffects.mList.size()); ++i)
        {
            const ESM::ENAMstruct& first = iter->mEffects.mList[i];
            const ESM::ENAMstruct& second = mEffects[i];

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

void MWMechanics::Alchemy::removeIngredients()
{
    for (TIngredientsContainer::iterator iter (mIngredients.begin()); iter!=mIngredients.end(); ++iter)
        if (!iter->isEmpty())
        {
            iter->getContainerStore()->remove(*iter, 1, mAlchemist);

            /*
                Start of tes3mp addition

                Store this item removal for later sending to avoid packet spam
            */
            mwmp::Main::get().getLocalPlayer()->storeItemRemoval(iter->getCellRef().getRefId(), 1);
            /*
                End of tes3mp addition
            */

            if (iter->getRefData().getCount()<1)
                *iter = MWWorld::Ptr();
        }

    updateEffects();
}

void MWMechanics::Alchemy::addPotion (const std::string& name)
{
    ESM::Potion newRecord;

    newRecord.mData.mWeight = 0;

    for (TIngredientsIterator iter (beginIngredients()); iter!=endIngredients(); ++iter)
        if (!iter->isEmpty())
            newRecord.mData.mWeight += iter->get<ESM::Ingredient>()->mBase->mData.mWeight;
    // new dwemcod weight logic begin
    if (countIngredients() > 0)
    {
        newRecord.mData.mWeight /= countIngredients();
        float weightHolder = newRecord.mData.mWeight;
        weightHolder = std::min(weightHolder, 1.0f);
        float weightReduction = getAlchemyFactor();
        weightReduction /= 100.0f;
        weightHolder -= weightReduction;
        weightHolder = std::max(weightHolder, 0.1f);
        newRecord.mData.mWeight = weightHolder;
    }
    // new weight logic end  

    newRecord.mData.mValue = mValue;
    newRecord.mData.mAutoCalc = 0;

    newRecord.mName = name;

    int index = Misc::Rng::rollDice(6);
    assert (index>=0 && index<6);

    static const char *meshes[] = { "standard", "bargain", "cheap", "fresh", "exclusive", "quality" };

    newRecord.mModel = "m\\misc_potion_" + std::string (meshes[index]) + "_01.nif";
    newRecord.mIcon = "m\\tx_potion_" + std::string (meshes[index]) + "_01.dds";

    newRecord.mEffects.mList = mEffects;

    /*
        Start of tes3mp change (major)

        Don't create a record and don't add the potion to the player's inventory;
        instead just store its record in preparation for sending it to the server
        and expect the server to add it to the player's inventory
    */
    /*
    const ESM::Potion* record = getRecord(newRecord);
    if (!record)
    {
        record = MWBase::Environment::get().getWorld()->createRecord(newRecord);
    }

    mAlchemist.getClass().getContainerStore (mAlchemist).add (record->mId, 1, mAlchemist);
    */
    mStoredPotion = newRecord;
    /*
        End of tes3mp change (major)
    */
}

void MWMechanics::Alchemy::increaseSkill()
{
    //dwemcod, now unused
    mAlchemist.getClass().skillUsageSucceeded (mAlchemist, ESM::Skill::Alchemy, 0);
}

float MWMechanics::Alchemy::getAlchemyFactor() const
{
    const CreatureStats& creatureStats = mAlchemist.getClass().getCreatureStats (mAlchemist);

    return
        (mAlchemist.getClass().getSkill(mAlchemist, ESM::Skill::Alchemy) +
        0.1f * creatureStats.getAttribute (ESM::Attribute::Intelligence).getModified()
        + 0.1f * creatureStats.getAttribute (ESM::Attribute::Luck).getModified());
}

int MWMechanics::Alchemy::countIngredients() const
{
    int ingredients = 0;

    for (TIngredientsIterator iter (beginIngredients()); iter!=endIngredients(); ++iter)
        if (!iter->isEmpty())
            ++ingredients;

    return ingredients;
}

int MWMechanics::Alchemy::countPotionsToBrew() const
{
    Result readyStatus = getReadyStatus();
    if (readyStatus != Result_Success)
        return 0;

    int toBrew = -1;

    for (TIngredientsIterator iter (beginIngredients()); iter!=endIngredients(); ++iter)
        if (!iter->isEmpty())
        {
            int count = iter->getRefData().getCount();
            if ((count > 0 && count < toBrew) || toBrew < 0)
                toBrew = count;
        }

    return toBrew;
}

void MWMechanics::Alchemy::setAlchemist (const MWWorld::Ptr& npc)
{
    mAlchemist = npc;

    mIngredients.resize (4);

    std::fill (mIngredients.begin(), mIngredients.end(), MWWorld::Ptr());

    mTools.resize (4);

    std::fill (mTools.begin(), mTools.end(), MWWorld::Ptr());

    mEffects.clear();

    MWWorld::ContainerStore& store = npc.getClass().getContainerStore (npc);

    for (MWWorld::ContainerStoreIterator iter (store.begin (MWWorld::ContainerStore::Type_Apparatus));
        iter!=store.end(); ++iter)
    {
        MWWorld::LiveCellRef<ESM::Apparatus>* ref = iter->get<ESM::Apparatus>();

        int type = ref->mBase->mData.mType;

        if (type<0 || type>=static_cast<int> (mTools.size()))
            throw std::runtime_error ("invalid apparatus type");

        if (!mTools[type].isEmpty())
            if (ref->mBase->mData.mQuality<=mTools[type].get<ESM::Apparatus>()->mBase->mData.mQuality)
                continue;

        mTools[type] = *iter;
    }
}

MWMechanics::Alchemy::TToolsIterator MWMechanics::Alchemy::beginTools() const
{
    return mTools.begin();
}

MWMechanics::Alchemy::TToolsIterator MWMechanics::Alchemy::endTools() const
{
    return mTools.end();
}

MWMechanics::Alchemy::TIngredientsIterator MWMechanics::Alchemy::beginIngredients() const
{
    return mIngredients.begin();
}

MWMechanics::Alchemy::TIngredientsIterator MWMechanics::Alchemy::endIngredients() const
{
    return mIngredients.end();
}

void MWMechanics::Alchemy::clear()
{
    mAlchemist = MWWorld::Ptr();
    mTools.clear();
    mIngredients.clear();
    mEffects.clear();
    setPotionName("");
}

void MWMechanics::Alchemy::setPotionName(const std::string& name)
{
    mPotionName = name;
}

int MWMechanics::Alchemy::addIngredient (const MWWorld::Ptr& ingredient)
{
    // find a free slot
    int slot = -1;

    for (int i=0; i<static_cast<int> (mIngredients.size()); ++i)
        if (mIngredients[i].isEmpty())
        {
            slot = i;
            break;
        }

    if (slot==-1)
        return -1;

    for (TIngredientsIterator iter (mIngredients.begin()); iter!=mIngredients.end(); ++iter)
        if (!iter->isEmpty() && Misc::StringUtils::ciEqual(ingredient.getCellRef().getRefId(),
                                                           iter->getCellRef().getRefId()))
            return -1;

    mIngredients[slot] = ingredient;

    updateEffects();

    return slot;
}

void MWMechanics::Alchemy::removeIngredient (int index)
{
    if (index>=0 && index<static_cast<int> (mIngredients.size()))
    {
        mIngredients[index] = MWWorld::Ptr();
        updateEffects();
    }
}

MWMechanics::Alchemy::TEffectsIterator MWMechanics::Alchemy::beginEffects() const
{
    return mEffects.begin();
}

MWMechanics::Alchemy::TEffectsIterator MWMechanics::Alchemy::endEffects() const
{
    return mEffects.end();
}

bool MWMechanics::Alchemy::knownEffect(unsigned int potionEffectIndex, const MWWorld::Ptr &npc)
{
    float alchemySkill = npc.getClass().getSkill (npc, ESM::Skill::Alchemy);
    static const float fWortChanceValue =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find("fWortChanceValue")->mValue.getFloat();
    return (potionEffectIndex <= 1 && alchemySkill >= fWortChanceValue)
            || (potionEffectIndex <= 3 && alchemySkill >= fWortChanceValue*2)
            || (potionEffectIndex <= 5 && alchemySkill >= fWortChanceValue*3)
            || (potionEffectIndex <= 7 && alchemySkill >= fWortChanceValue*4);
}

MWMechanics::Alchemy::Result MWMechanics::Alchemy::getReadyStatus() const
{
    if (mTools[ESM::Apparatus::MortarPestle].isEmpty())
        return Result_NoMortarAndPestle;

    if (countIngredients()<2)
        return Result_LessThanTwoIngredients;

    if (mPotionName.empty())
        return Result_NoName;

    if (listEffects().empty())
        return Result_NoEffects;

    return Result_Success;
}

MWMechanics::Alchemy::Result MWMechanics::Alchemy::create (const std::string& name, int& count)
{
    /*
        Start of tes3mp addition

        Instead of sending an ID_PLAYER_INVENTORY packet for every ingredient removal in
        ContainerStore::remove(), as that would get very spammy when many potions are created
        at the same time, just avoid sending packets here and store the item removals so they
        can be sent in a single packet when all the potions have been created
    */
    mwmp::Main::get().getLocalPlayer()->avoidSendingInventoryPackets = true;
    /*
        End of tes3mp addition
    */

    setPotionName(name);
    Result readyStatus = getReadyStatus();

    if (readyStatus == Result_NoEffects)
        removeIngredients();

    /*
        Start of tes3mp change (minor)

        Set avoidSendingInventoryPackets to false again if this has not been a successful
        potion creation
    */
    if (readyStatus != Result_Success)
    {
        mwmp::Main::get().getLocalPlayer()->avoidSendingInventoryPackets = false;
        return readyStatus;
    }
    /*
        End of tes3mp change (major)
    */

    Result result = Result_RandomFailure;
    int brewedCount = 0;
    for (int i = 0; i < count; ++i)
    {
        if (createSingle() == Result_Success)
        {
            result = Result_Success;
            brewedCount++;
        }
    }

    count = brewedCount;

    /*
        Start of tes3mp addition

        Send an ID_RECORD_DYNAMIC packet with the potion we've been creating
        now that we know its quantity

        Stop avoiding the sending of ID_PLAYER_INVENTORY packets and send all
        item removals stored so far
    */
    mwmp::Main::get().getNetworking()->getWorldstate()->sendPotionRecord(&mStoredPotion, brewedCount);
    mwmp::Main::get().getLocalPlayer()->avoidSendingInventoryPackets = false;
    mwmp::Main::get().getLocalPlayer()->sendStoredItemRemovals();
    /*
        End of tes3mp addition
    */

    return result;
}

MWMechanics::Alchemy::Result MWMechanics::Alchemy::createSingle ()
{

    //dwemer coda, sum ingredient values
    int numberIngredients = countIngredients();
    int sumIngredientValue = 0;
    for (TIngredientsIterator it = beginIngredients(); it != endIngredients(); ++it)
    {
        if (it->isEmpty()) continue;

        auto *wrap = it->get<ESM::Ingredient>();
        if (!wrap) continue;

        auto *base = wrap->mBase;
        if (!base) continue;

        sumIngredientValue += base->mData.mValue;
    }

    float averageIngredientValue = 0.0f;

    if ((sumIngredientValue > 0) && (numberIngredients > 0))
    {
        averageIngredientValue = static_cast<float>(sumIngredientValue) / static_cast<float>(numberIngredients);
    }

    //dwemer coda sum value end

    if (beginEffects() == endEffects())
    {
        // all effects were nullified due to insufficient skill
        removeIngredients();
        return Result_RandomFailure;
    }

    //dwemcod, increase base success chance
    float successChance = 30.0f;
    successChance += ( getAlchemyFactor() / 1.5f);

    //dwemcod, ingredients add to success chance
    float itemSuccessAddition = 0.0f;

    if (averageIngredientValue >= 10.0f)
    {
        itemSuccessAddition = (0.158f * averageIngredientValue);
        itemSuccessAddition += 8.42f;
    }

    successChance += itemSuccessAddition;


    if (successChance < Misc::Rng::roll0to99())
    {
        removeIngredients();
        return Result_RandomFailure;
    }

    addPotion(mPotionName);

    removeIngredients();

    //added the content of increaseskill here so it has access to the above variables, and commented out the call


    float alchemySkill = mAlchemist.getClass().getSkill(mAlchemist, ESM::Skill::Alchemy);

    float alchXpMod = 1.0f;

    //reduction in XP from potions with avg ingredient values less than 5gp
    //to reduce the 1gp ingredient spamming
    //even this might be too generous
    if (averageIngredientValue < 5.0f)
    {
        alchXpMod = 0.5f;

        if (alchemySkill > 30.0f)
        {
            alchXpMod = 0.25f;
        }

        if (alchemySkill > 60.0f)
        {
            alchXpMod = 0.125f;
        }

        if (alchemySkill > 90.0f)
        {
            alchXpMod = 0.05f;
        }
    }

    mAlchemist.getClass().skillUsageSucceeded(mAlchemist, ESM::Skill::Alchemy, 0, alchXpMod);
    //increaseSkill();

    return Result_Success;
}

std::string MWMechanics::Alchemy::suggestPotionName()
{
    std::set<MWMechanics::EffectKey> effects = listEffects();
    if (effects.empty())
        return "";

    int effectId = effects.begin()->mId;
    return MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find(
                ESM::MagicEffect::effectIdToString(effectId))->mValue.getString();
}

std::vector<std::string> MWMechanics::Alchemy::effectsDescription (const MWWorld::ConstPtr &ptr, const int alchemySkill)
{
    std::vector<std::string> effects;

    const auto& item = ptr.get<ESM::Ingredient>()->mBase;
    const auto& gmst = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>();
    const static auto fWortChanceValue = gmst.find("fWortChanceValue")->mValue.getFloat();
    const auto& data = item->mData;

    for (auto i = 0; i < 4; ++i)
    {
        const auto effectID = data.mEffectID[i];
        const auto skillID = data.mSkills[i];
        const auto attributeID = data.mAttributes[i];

        if (alchemySkill < fWortChanceValue * (i + 1))
            break;

        if (effectID != -1)
        {
            std::string effect = gmst.find(ESM::MagicEffect::effectIdToString(effectID))->mValue.getString();

            if (skillID != -1)
                effect += " " + gmst.find(ESM::Skill::sSkillNameIds[skillID])->mValue.getString();
            else if (attributeID != -1)
                effect += " " + gmst.find(ESM::Attribute::sGmstAttributeIds[attributeID])->mValue.getString();

            effects.push_back(effect);

        }
    }
    return effects;
}
