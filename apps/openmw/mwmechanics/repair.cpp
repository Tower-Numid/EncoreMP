#include "repair.hpp"

#include <components/misc/rng.hpp>

/*
    Start of tes3mp addition

    Include additional headers for multiplayer purposes
*/
#include "../mwmp/Main.hpp"
#include "../mwmp/Networking.hpp"
#include "../mwmp/LocalPlayer.hpp"
#include "../mwmp/MechanicsHelper.hpp"
/*
    End of tes3mp addition
*/

#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"
#include "../mwbase/windowmanager.hpp"

#include "../mwworld/containerstore.hpp"
#include "../mwworld/class.hpp"
#include "../mwworld/esmstore.hpp"

#include "creaturestats.hpp"
#include "actorutil.hpp"

#include "../mwworld/inventorystore.hpp"

namespace MWMechanics
{

void Repair::repair(const MWWorld::Ptr &itemToRepair)
{
    MWWorld::Ptr player = getPlayer();
    MWWorld::LiveCellRef<ESM::Repair> *ref =
        mTool.get<ESM::Repair>();

    // unstack tool if required
    player.getClass().getContainerStore(player).unstack(mTool, player);

    // reduce number of uses left
    int uses = mTool.getClass().getItemHealth(mTool);
    uses -= std::min(uses, 1);
    mTool.getCellRef().setCharge(uses);

    MWMechanics::CreatureStats& stats = player.getClass().getCreatureStats(player);

    float fatigueTerm = stats.getFatigueTerm();
    float pcStrength = stats.getAttribute(ESM::Attribute::Strength).getModified();
    float pcLuck = stats.getAttribute(ESM::Attribute::Luck).getModified();
    float armorerSkill = player.getClass().getSkill(player, ESM::Skill::Armorer);

    float fRepairAmountMult = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>()
            .find("fRepairAmountMult")->mValue.getFloat();

    float toolQuality = ref->mBase->mData.mQuality;

    float x = (0.1f * pcStrength + 0.1f * pcLuck + armorerSkill) * fatigueTerm;

    //get item value
    int basePrice = std::max(1, itemToRepair.getClass().getValue(itemToRepair));

    auto slotPair = itemToRepair.getClass().getEquipmentSlots(itemToRepair);
    const std::vector<int> &slots = slotPair.first;

    // assign item a difficulty tier based on cost

    int tier = 1;

    if (basePrice <= 100)
    {
        tier = 1;
    }
    if (basePrice > 100)
    {
        tier = 2;
    }
    if (basePrice >= 500)
    {
        tier = 3;
    }
    if (basePrice >= 2000)
    {
        tier = 4;
    }
    if (basePrice >= 5000)
    {
        tier = 5;
    }
    if (basePrice >= 20000)
    {
        tier = 6;
    }
    if (basePrice >= 50000)
    {
        tier = 7;
    }


    // split items into weapons and armours

    if (!slots.empty())
    {
        if (slots[0] == static_cast<int>(MWWorld::InventoryStore::Slot_CarriedRight))
        {

            // step down of difficulty for all early and mig-game weapons, to help keep skill non-essential
            if (tier == 2)
            {
                tier = 1;
            }
            if (tier == 3)
            {
                tier = 2;
            }
            if (tier == 4)
            {
                tier = 3;
            }
        }
    }


    // V1 balance pass, reduce the fatigue term so that at full you are at 1x mod
    // easier to balance around this, and you will never realistically choose to repair at low fatigue
    fatigueTerm -= 0.25f;


    // calculate base percent, aka player term
    float basepercent = (0.1f * pcStrength + 0.1f * pcLuck + armorerSkill) * fatigueTerm;


    // EncoreMP, new tool quality adjustments start

    if (toolQuality > 1.0f)
    {
        float qualitymod = (toolQuality - 1.0f);
        qualitymod *= 10.0f;
        qualitymod *= 1.50f;
        basepercent += qualitymod;
    }


    // a hard cap, some guarding to avoid silly numbers appearing in nonlinear squaring equations
    // this does impose an arbitrarily high but final cap on amount repaired per swing, as values of x beyond 100 do help

    if (basepercent > 500.0f)
    {
        basepercent = 500.0f;
    }


    if (tier == 1)
    {
        x = ((0.0136f * basepercent * basepercent) + (0.59f * basepercent) - 6.75f);
        if (x < 20.0f)
        {
            x = 20.0f;
        }
    }

    if (tier == 2)
    {
        x = ((0.0128f * basepercent * basepercent) + (0.399f * basepercent) - 4.89f);
        if (x < 17.0f)
        {
            x = 17.0f;
        }
    }

    if (tier == 3)
    {
        if (slots[0] == static_cast<int>(MWWorld::InventoryStore::Slot_CarriedRight))
        {
            /// the tier 3.5 version, whcih is slightly harder than 3 but still easier than the 4 weapons would otherwise be
            x = ((0.0051f * basepercent * basepercent) + (1.121f * basepercent) - 39.15f);
            if (x < 14.0f)
            {
                x = 14.0f;
            }
        }

        else
        {
            x = ((0.0033f * basepercent * basepercent) + (1.342f * basepercent) - 30.0f);
            if (x < 15.0f)
            {
                x = 15.0f;
            }
        }
    }

    if (tier == 4)
    {
        x = ((0.0035f * basepercent * basepercent) + (1.21f * basepercent) - 36.34f);
        if (x < 10.0f)
        {
            x = 10.0f;
        }
    }

    if (tier == 5)
    {
        x = ((0.0114f * basepercent * basepercent) + (0.23f * basepercent) - 27.64f);
        if (x < 7.0f)
        {
            x = 7.0f;
        }
    }

    if (tier == 6)
    {
        x = ((0.0072f * basepercent * basepercent) + (0.51f * basepercent) - 41.4f);
        if (x < 5.0f)
        {
            x = 5.0f;
        }
    }

    if (tier == 7)
    {
        x = ((0.014f * basepercent * basepercent) - (0.552f * basepercent) - 14.63f);
        if (x < 5.0f)
        {
            x = 5.0f;
        }
    }


    //item value influencing difficulty of repair

    int roll = Misc::Rng::roll0to99();
    if (roll <= x)
    {
        int y = static_cast<int>(fRepairAmountMult * toolQuality * roll);
        y = std::max(1, y);

        // repair by 'y' points
        int charge = itemToRepair.getClass().getItemHealth(itemToRepair);
        charge = std::min(charge + y, itemToRepair.getClass().getItemMaxHealth(itemToRepair));

        /*
            Start of tes3mp change (minor)

            Send PlayerInventory packets that replace the original item with the new one
        */
        mwmp::LocalPlayer *localPlayer = mwmp::Main::get().getLocalPlayer();
        mwmp::Item removedItem = MechanicsHelper::getItem(itemToRepair, 1);

        itemToRepair.getCellRef().setCharge(charge);

        mwmp::Item addedItem = MechanicsHelper::getItem(itemToRepair, 1);

        localPlayer->sendItemChange(addedItem, mwmp::InventoryChanges::ADD);
        localPlayer->sendItemChange(removedItem, mwmp::InventoryChanges::REMOVE);
        /*
            End of tes3mp change (minor)
        */

        // attempt to re-stack item, in case it was fully repaired
        MWWorld::ContainerStoreIterator stacked = player.getClass().getContainerStore(player).restack(itemToRepair);

        // set the OnPCRepair variable on the item's script
        std::string script = stacked->getClass().getScript(itemToRepair);
        if(script != "")
            stacked->getRefData().getLocals().setVarByInt(script, "onpcrepair", 1);

        // increase skill
        player.getClass().skillUsageSucceeded(player, ESM::Skill::Armorer, 0);

        MWBase::Environment::get().getWindowManager()->playSound("Repair", 0.5f, 1.f);
        MWBase::Environment::get().getWindowManager()->messageBox("#{sRepairSuccess}");

        /*
            Start of tes3mp addition

            Send an ID_OBJECT_SOUND packet every time the player makes a sound here
        */
        mwmp::ObjectList *objectList = mwmp::Main::get().getNetworking()->getObjectList();
        objectList->reset();
        objectList->packetOrigin = mwmp::CLIENT_GAMEPLAY;
        objectList->addObjectSound(MWMechanics::getPlayer(), "Repair", 0.5f, 1.0);
        objectList->sendObjectSound();
        /*
            End of tes3mp addition
        */
    }
    else
    {
        MWBase::Environment::get().getWindowManager()->playSound("Repair Fail", 0.5f, 1.f);
        MWBase::Environment::get().getWindowManager()->messageBox("#{sRepairFailed}");

        /*
            Start of tes3mp addition

            Send an ID_OBJECT_SOUND packet every time the player makes a sound here
        */
        mwmp::ObjectList *objectList = mwmp::Main::get().getNetworking()->getObjectList();
        objectList->reset();
        objectList->packetOrigin = mwmp::CLIENT_GAMEPLAY;
        objectList->addObjectSound(MWMechanics::getPlayer(), "Repair Fail", 0.5f, 1.0);
        objectList->sendObjectSound();
        /*
            End of tes3mp addition
        */
    }

    // tool used up?
    if (mTool.getCellRef().getCharge() == 0)
    {
        MWWorld::ContainerStore& store = player.getClass().getContainerStore(player);

        store.remove(mTool, 1, player);

        std::string message = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>()
                .find("sNotifyMessage51")->mValue.getString();
        message = Misc::StringUtils::format(message, mTool.getClass().getName(mTool));

        MWBase::Environment::get().getWindowManager()->messageBox(message);

        // try to find a new tool of the same ID
        for (MWWorld::ContainerStoreIterator iter (store.begin());
             iter!=store.end(); ++iter)
        {
            if (Misc::StringUtils::ciEqual(iter->getCellRef().getRefId(), mTool.getCellRef().getRefId()))
            {
                mTool = *iter;

                MWBase::Environment::get().getWindowManager()->playSound("Item Repair Up");

                break;
            }
        }
    }
}

}
