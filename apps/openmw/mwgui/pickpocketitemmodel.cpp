#include "pickpocketitemmodel.hpp"

#include <components/misc/rng.hpp>
#include <components/esm/loadskil.hpp>

#include "../mwmechanics/actorutil.hpp"
#include "../mwmechanics/creaturestats.hpp"
#include "../mwmechanics/pickpocket.hpp"

#include "../mwworld/class.hpp"

#include "../mwbase/environment.hpp"
#include "../mwbase/mechanicsmanager.hpp"
#include "../mwbase/windowmanager.hpp"

namespace MWGui
{

    PickpocketItemModel::PickpocketItemModel(const MWWorld::Ptr& actor, ItemModel *sourceModel, bool hideItems)
        : mActor(actor), mPickpocketDetected(false)
    {
        MWWorld::Ptr player = MWMechanics::getPlayer();
        mSourceModel = sourceModel;
        //float chance = player.getClass().getSkill(player, ESM::Skill::Sneak);

        //updated chance logic to better mirror pickpocket success chance logic
        //note however that this does not include the fatigue term, an intentional choice
        //so by balancing around a 50% chance to steal, I am actually setting a baseline chance of 62.5% if the player is full fatigue
        const MWMechanics::CreatureStats &playerStats = player.getClass().getCreatureStats(player);
        float luck = playerStats.getAttribute(ESM::Attribute::Luck).getModified();
        float agility = playerStats.getAttribute(ESM::Attribute::Agility).getModified();
        float sneak = player.getClass().getSkill(player, ESM::Skill::Sneak);
        float chance = (sneak + (agility * 0.2) + (luck * 0.1));


        // gold per skill level logic, will mirror what the steal chances are

        chance *= 5.0f;

        //

        mSourceModel->update();

        // build list of items that player is unable to find when attempts to pickpocket.
        if (hideItems)
        {
            for (size_t i = 0; i<mSourceModel->getItemCount(); ++i)
            {
                const ItemStack& item = mSourceModel->getItem(i);
                MWWorld::Ptr itemPtr = item.mBase;
                if (itemPtr.isEmpty())
                    continue; // don't know if I strictly needed to do this, but it's a robust guarding, I think technically
                              // some NPCs can carry light sources as psuedo items

                int singleValue = itemPtr.getClass().getValue(itemPtr);
                int count = item.mCount;
                float stackValue = static_cast<float>(singleValue) * static_cast<float>(count);

                //float chanceMod = (chance * 10.0f);

                if (stackValue > chance)
                {
                    mHiddenItems.push_back(mSourceModel->getItem(i));
                }
            }
        }
    }

    bool PickpocketItemModel::allowedToUseItems() const
    {
        return false;
    }

    ItemStack PickpocketItemModel::getItem (ModelIndex index)
    {
        if (index < 0)
            throw std::runtime_error("Invalid index supplied");
        if (mItems.size() <= static_cast<size_t>(index))
            throw std::runtime_error("Item index out of range");
        return mItems[index];
    }

    size_t PickpocketItemModel::getItemCount()
    {
        return mItems.size();
    }

    void PickpocketItemModel::update()
    {
        mSourceModel->update();
        mItems.clear();
        for (size_t i = 0; i<mSourceModel->getItemCount(); ++i)
        {
            const ItemStack& item = mSourceModel->getItem(i);

            // Bound items may not be stolen
            if (item.mFlags & ItemStack::Flag_Bound)
                continue;

            // EncoreMP, slight restructure of logic, an attempt at some backend guarding

            bool itemHidden = false;
            for (const ItemStack &h : mHiddenItems)
            {
                if (h.mBase.isEmpty()) continue;
                if (item.mBase.isEmpty()) { itemHidden = false; break; }
                if (h.mBase == item.mBase) { itemHidden = true; break; }
            }
            if (!itemHidden && item.mType != ItemStack::Type_Equipped && !(item.mFlags & ItemStack::Flag_Bound))
                mItems.push_back(item);


            //original logic
            //if (std::find(mHiddenItems.begin(), mHiddenItems.end(), item) == mHiddenItems.end()
            //        && item.mType != ItemStack::Type_Equipped)
            //   mItems.push_back(item);
        }
    }

    void PickpocketItemModel::removeItem (const ItemStack &item, size_t count)
    {
        ProxyItemModel::removeItem(item, count);
    }

    bool PickpocketItemModel::onDropItem(const MWWorld::Ptr &item, int count)
    {
        // don't allow "reverse pickpocket" (it will be handled by scripts after 1.0)
        return false;
    }

    void PickpocketItemModel::onClose()
    {
        // Make sure we were actually closed, rather than just temporarily hidden (e.g. console or main menu opened)
        if (MWBase::Environment::get().getWindowManager()->containsMode(GM_Container)
        // If it was already detected while taking an item, no need to check now
                || mPickpocketDetected)
            return;

        MWWorld::Ptr player = MWMechanics::getPlayer();
        MWMechanics::Pickpocket pickpocket(player, mActor);
        if (pickpocket.finish())
        {
            MWBase::Environment::get().getMechanicsManager()->commitCrime(
                        player, mActor, MWBase::MechanicsManager::OT_Pickpocket, std::string(), 0, true);
            MWBase::Environment::get().getWindowManager()->removeGuiMode(MWGui::GM_Container);
            mPickpocketDetected = true;
        }
    }

    bool PickpocketItemModel::onTakeItem(const MWWorld::Ptr &item, int count)
    {
        if (mActor.getClass().getCreatureStats(mActor).getKnockedDown())
            return mSourceModel->onTakeItem(item, count);

        bool success = stealItem(item, count);
        if (success)
        {
            MWWorld::Ptr player = MWMechanics::getPlayer();
            MWBase::Environment::get().getMechanicsManager()->itemTaken(player, item, mActor, count, false);
        }

        return success;
    }

    bool PickpocketItemModel::stealItem(const MWWorld::Ptr &item, int count)
    {
        MWWorld::Ptr player = MWMechanics::getPlayer();
        MWMechanics::Pickpocket pickpocket(player, mActor);
        if (pickpocket.pick(item, count))
        {
            MWBase::Environment::get().getMechanicsManager()->commitCrime(
                        player, mActor, MWBase::MechanicsManager::OT_Pickpocket, std::string(), 0, true);
            MWBase::Environment::get().getWindowManager()->removeGuiMode(MWGui::GM_Container);
            mPickpocketDetected = true;
            return false;
        }
        else
            player.getClass().skillUsageSucceeded(player, ESM::Skill::Sneak, 1);

        return true;
    }
}
