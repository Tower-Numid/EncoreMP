#include "pickpocket.hpp"

#include <components/misc/rng.hpp>

#include "../mwworld/class.hpp"
#include "../mwworld/esmstore.hpp"

#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"

#include "npcstats.hpp"

namespace MWMechanics
{

    Pickpocket::Pickpocket(const MWWorld::Ptr &thief, const MWWorld::Ptr &victim)
        : mThief(thief)
        , mVictim(victim)
    {
    }

    float Pickpocket::getChanceModifier(const MWWorld::Ptr &ptr, float add)
    {
        NpcStats& stats = ptr.getClass().getNpcStats(ptr);
        float agility = stats.getAttribute(ESM::Attribute::Agility).getModified();
        float luck = stats.getAttribute(ESM::Attribute::Luck).getModified();
        float sneak = static_cast<float>(ptr.getClass().getSkill(ptr, ESM::Skill::Sneak));
        return (add + 0.2f * agility + 0.1f * luck + sneak) * stats.getFatigueTerm();
    }

    bool Pickpocket::getDetected(float valueTerm)
    {
        // EncoreMP, complete function overhaul to mirror pickpocketing UI window
        float playerTerm = getChanceModifier(mThief);

        float itemValue = valueTerm;

        itemValue = std::max(itemValue, 1.0f);

        float itemDifficulty = (itemValue / 5.0f);

        float difficultyMod = (playerTerm - itemDifficulty);

        difficultyMod *= 1.50f;

        int successChance = 50;

        successChance += static_cast<int>(difficultyMod);

        int iPickMinChance = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>()
            .find("iPickMinChance")->mValue.getInteger();
        int iPickMaxChance = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>()
            .find("iPickMaxChance")->mValue.getInteger();

        int roll = Misc::Rng::roll0to99();

        successChance = std::min(int(iPickMaxChance), successChance);
        successChance = std::max(int(iPickMinChance), successChance);

        if (successChance > roll)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool Pickpocket::pick(MWWorld::Ptr item, int count)
    {
        float stackValue = static_cast<float>(item.getClass().getValue(item) * count);
        float fPickPocketMod = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>()
                .find("fPickPocketMod")->mValue.getFloat();
        float valueTerm = fPickPocketMod * stackValue;
        // EncoreMP, changed GMST behaviour by removing 10x mult, now value is difficulty if GMST is 1

        return getDetected(valueTerm);
    }

    bool Pickpocket::finish()
    {
        // EncoreMP, now the player will never be caught just from closing the window
        return false;
    }

}
