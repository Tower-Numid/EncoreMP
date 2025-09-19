#include "trading.hpp"

#include <components/misc/rng.hpp>

#include "../mwbase/environment.hpp"
#include "../mwbase/mechanicsmanager.hpp"
#include "../mwbase/world.hpp"

#include "../mwworld/class.hpp"
#include "../mwworld/esmstore.hpp"

#include "creaturestats.hpp"

namespace MWMechanics
{
    Trading::Trading() {}

    bool Trading::haggle(const MWWorld::Ptr& player, const MWWorld::Ptr& merchant, int playerOffer, int merchantOffer)
    {
        // accept if merchant offer is better than player offer
        if ( playerOffer <= merchantOffer ) {
            return true;
        }

        // reject if npc is a creature
        if ( merchant.getTypeName() != typeid(ESM::NPC).name() ) {
            return false;
        }

        const MWWorld::Store<ESM::GameSetting> &gmst =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>();

        // Is the player buying?
        bool buying = (merchantOffer < 0);
        int a = std::abs(merchantOffer);
        int b = std::abs(playerOffer);
        int d = (buying)
            ? int(100 * (a - b) / a)
            : int(100 * (b - a) / b);

        int clampedDisposition = MWBase::Environment::get().getMechanicsManager()->getDerivedDisposition(merchant);

        const MWMechanics::CreatureStats &merchantStats = merchant.getClass().getCreatureStats(merchant);
        const MWMechanics::CreatureStats &playerStats = player.getClass().getCreatureStats(player);

        float a1 = static_cast<float>(player.getClass().getSkill(player, ESM::Skill::Mercantile));
        float b1 = 0.1f * playerStats.getAttribute(ESM::Attribute::Luck).getModified();
        float c1 = 0.2f * playerStats.getAttribute(ESM::Attribute::Personality).getModified();
        float d1 = static_cast<float>(merchant.getClass().getSkill(merchant, ESM::Skill::Mercantile));
        float e1 = 0.1f * merchantStats.getAttribute(ESM::Attribute::Luck).getModified();
        float f1 = 0.2f * merchantStats.getAttribute(ESM::Attribute::Personality).getModified();

        float dispositionTerm = gmst.find("fDispositionMod")->mValue.getFloat() * (clampedDisposition - 50);
        float pcTerm = (dispositionTerm + a1 + b1 + c1) * playerStats.getFatigueTerm();
        float npcTerm = (d1 + e1 + f1) * merchantStats.getFatigueTerm();
        float x = gmst.find("fBargainOfferMulti")->mValue.getFloat() * d
            + gmst.find("fBargainOfferBase")->mValue.getFloat()
            + int(pcTerm - npcTerm);

        //temporary cap to success, when an item value would be haggled by more than 10% each way the offer is always refused
        //this is to account for the current ability to exceed the buy/sell ratio and make infinite money, via haggling

        float ratio = std::abs(float(playerOffer)) / std::abs(float(merchantOffer));
        if (ratio < 0.9f || ratio > 1.1f)
        {
            x = 0.0f;
        }

        //end of haggle cap system

        int roll = Misc::Rng::rollDice(100) + 1;

        // reject if roll fails
        // (or if player tries to buy things and get money)
        if ( roll > x || (merchantOffer < 0 && 0 < playerOffer) ) {
            return false;
        }



        return true;
    }
}
