#include <cmath>

#include "spellutil.hpp"

#include <limits>

#include "../mwbase/environment.hpp"
#include "../mwbase/windowmanager.hpp"
#include "../mwbase/world.hpp"

#include "../mwworld/class.hpp"
#include "../mwworld/esmstore.hpp"

#include "actorutil.hpp"
#include "creaturestats.hpp"

namespace MWMechanics
{
    ESM::Skill::SkillEnum spellSchoolToSkill(int school)
    {
        static const std::array<ESM::Skill::SkillEnum, 6> schoolSkillArray
        {
            ESM::Skill::Alteration, ESM::Skill::Conjuration, ESM::Skill::Destruction,
            ESM::Skill::Illusion, ESM::Skill::Mysticism, ESM::Skill::Restoration
        };
        return schoolSkillArray.at(school);
    }

    float calcEffectCost(const ESM::ENAMstruct& effect, const ESM::MagicEffect* magicEffect, bool useNpcCost)
    {
        const MWWorld::ESMStore& store = MWBase::Environment::get().getWorld()->getStore();
        if (!magicEffect)
            magicEffect = store.get<ESM::MagicEffect>().find(effect.mEffectID);
        bool hasMagnitude = !(magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude);
        bool hasDuration = !(magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration);
        bool appliedOnce = magicEffect->mData.mFlags & ESM::MagicEffect::AppliedOnce;
        int minMagn = hasMagnitude ? effect.mMagnMin : 1;
        int maxMagn = hasMagnitude ? effect.mMagnMax : 1;
        int duration = hasDuration ? effect.mDuration : 1;
        if (!appliedOnce)
            duration = std::max(1, duration);
        static const float fEffectCostMult = store.get<ESM::GameSetting>().find("fEffectCostMult")->mValue.getFloat();

        float effectCost = 1.0f;

        if (useNpcCost == false)
        {
            // Player behaviour, use live ESP mBaseCost values
            effectCost = magicEffect->mData.mBaseCost;
        }
        else
        {
            // NPC fork, use hardcoded base game values as per this function
            effectCost = getBaseGameEffectCost(effect.mEffectID);
        }

        float x = 0.5 * (std::max(1, minMagn) + std::max(1, maxMagn));
        x *= 0.1 * effectCost;
        x *= 1 + duration;
        x += 0.05 * std::max(1, effect.mArea) * effectCost;

        return x * fEffectCostMult;
    }

    int getEffectiveEnchantmentCastCost(float castCost, const MWWorld::Ptr &actor)
    {
        /*
         * Each point of enchant skill above/under 10 subtracts/adds
         * one percent of enchantment cost while minimum is 1.
         */
        int eSkill = actor.getClass().getSkill(actor, ESM::Skill::Enchant);

        if (eSkill < 1)
            eSkill = 1;
        else if (eSkill > 200)
            eSkill = 200;

        int intPart = static_cast<int>(castCost * (0.67 / std::exp(eSkill * 0.004 * std::log(eSkill))));

        const float result = intPart + 1 + (castCost / 3);

        return static_cast<int>((result < 1) ? 1 : result);
    }

    float getBaseGameEffectCost(int effectID)
    {
        switch (effectID)
        {
        case ESM::MagicEffect::WaterBreathing:           return 3.0f;
        case ESM::MagicEffect::SwiftSwim:                return 2.0f;
        case ESM::MagicEffect::WaterWalking:             return 3.0f;
        case ESM::MagicEffect::Shield:                   return 2.0f;
        case ESM::MagicEffect::FireShield:               return 3.0f;
        case ESM::MagicEffect::LightningShield:          return 3.0f;
        case ESM::MagicEffect::FrostShield:              return 3.0f;
        case ESM::MagicEffect::Burden:                   return 1.0f;
        case ESM::MagicEffect::Feather:                  return 1.0f;
        case ESM::MagicEffect::Jump:                     return 3.0f;
        case ESM::MagicEffect::Levitate:                 return 3.0f;
        case ESM::MagicEffect::SlowFall:                 return 3.0f;
        case ESM::MagicEffect::Lock:                     return 2.0f;
        case ESM::MagicEffect::Open:                     return 6.0f;
        case ESM::MagicEffect::FireDamage:               return 5.0f;
        case ESM::MagicEffect::ShockDamage:              return 7.0f;
        case ESM::MagicEffect::FrostDamage:              return 5.0f;
        case ESM::MagicEffect::DrainAttribute:           return 1.0f;
        case ESM::MagicEffect::DrainHealth:              return 4.0f;
        case ESM::MagicEffect::DrainMagicka:             return 4.0f;
        case ESM::MagicEffect::DrainFatigue:             return 2.0f;
        case ESM::MagicEffect::DrainSkill:               return 1.0f;
        case ESM::MagicEffect::DamageAttribute:          return 8.0f;
        case ESM::MagicEffect::DamageHealth:             return 8.0f;
        case ESM::MagicEffect::DamageMagicka:            return 8.0f;
        case ESM::MagicEffect::DamageFatigue:            return 4.0f;
        case ESM::MagicEffect::DamageSkill:              return 8.0f;
        case ESM::MagicEffect::Poison:                   return 9.0f;
        case ESM::MagicEffect::WeaknessToFire:           return 2.0f;
        case ESM::MagicEffect::WeaknessToFrost:          return 2.0f;
        case ESM::MagicEffect::WeaknessToShock:          return 2.0f;
        case ESM::MagicEffect::WeaknessToMagicka:        return 2.0f;
        case ESM::MagicEffect::WeaknessToCommonDisease:  return 2.0f;
        case ESM::MagicEffect::WeaknessToBlightDisease:  return 4.0f;
        case ESM::MagicEffect::WeaknessToCorprusDisease: return 4.0f;
        case ESM::MagicEffect::WeaknessToPoison:         return 2.0f;
        case ESM::MagicEffect::WeaknessToNormalWeapons:  return 2.0f;
        case ESM::MagicEffect::DisintegrateWeapon:       return 6.0f;
        case ESM::MagicEffect::DisintegrateArmor:        return 6.0f;
        case ESM::MagicEffect::Invisibility:             return 20.0f;
        case ESM::MagicEffect::Chameleon:                return 1.0f;
        case ESM::MagicEffect::Light:                    return 0.2f;
        case ESM::MagicEffect::Sanctuary:                return 1.0f;
        case ESM::MagicEffect::NightEye:                 return 0.2f;
        case ESM::MagicEffect::Charm:                    return 5.0f;
        case ESM::MagicEffect::Paralyze:                 return 40.0f;
        case ESM::MagicEffect::Silence:                  return 40.0f;
        case ESM::MagicEffect::Blind:                    return 1.0f;
        case ESM::MagicEffect::Sound:                    return 3.0f;
        case ESM::MagicEffect::CalmHumanoid:             return 1.0f;
        case ESM::MagicEffect::CalmCreature:             return 1.0f;
        case ESM::MagicEffect::FrenzyHumanoid:           return 1.0f;
        case ESM::MagicEffect::FrenzyCreature:           return 1.0f;
        case ESM::MagicEffect::DemoralizeHumanoid:       return 1.0f;
        case ESM::MagicEffect::DemoralizeCreature:       return 1.0f;
        case ESM::MagicEffect::RallyHumanoid:            return 0.2f;
        case ESM::MagicEffect::RallyCreature:            return 0.2f;
        case ESM::MagicEffect::Dispel:                   return 5.0f;
        case ESM::MagicEffect::Soultrap:                 return 2.0f;
        case ESM::MagicEffect::Telekinesis:              return 1.0f;
        case ESM::MagicEffect::Mark:                     return 350.0f;
        case ESM::MagicEffect::Recall:                   return 350.0f;
        case ESM::MagicEffect::DivineIntervention:       return 150.0f;
        case ESM::MagicEffect::AlmsiviIntervention:      return 150.0f;
        case ESM::MagicEffect::DetectAnimal:             return 0.75f;
        case ESM::MagicEffect::DetectEnchantment:        return 1.0f;
        case ESM::MagicEffect::DetectKey:                return 1.0f;
        case ESM::MagicEffect::SpellAbsorption:          return 10.0f;
        case ESM::MagicEffect::Reflect:                  return 10.0f;
        case ESM::MagicEffect::CureCommonDisease:        return 300.0f;
        case ESM::MagicEffect::CureBlightDisease:        return 2000.0f;
        case ESM::MagicEffect::CureCorprusDisease:       return 2500.0f;
        case ESM::MagicEffect::CurePoison:               return 100.0f;
        case ESM::MagicEffect::CureParalyzation:         return 100.0f;
        case ESM::MagicEffect::RestoreAttribute:         return 1.0f;
        case ESM::MagicEffect::RestoreHealth:            return 5.0f;
        case ESM::MagicEffect::RestoreMagicka:           return 5.0f;
        case ESM::MagicEffect::RestoreFatigue:           return 1.0f;
        case ESM::MagicEffect::RestoreSkill:             return 1.0f;
        case ESM::MagicEffect::FortifyAttribute:         return 1.0f;
        case ESM::MagicEffect::FortifyHealth:            return 1.0f;
        case ESM::MagicEffect::FortifyMagicka:           return 1.0f;
        case ESM::MagicEffect::FortifyFatigue:           return 0.5f;
        case ESM::MagicEffect::FortifySkill:             return 1.0f;
        case ESM::MagicEffect::FortifyMaximumMagicka:    return 4.0f;
        case ESM::MagicEffect::AbsorbAttribute:          return 2.0f;
        case ESM::MagicEffect::AbsorbHealth:             return 8.0f;
        case ESM::MagicEffect::AbsorbMagicka:            return 8.0f;
        case ESM::MagicEffect::AbsorbFatigue:            return 4.0f;
        case ESM::MagicEffect::AbsorbSkill:              return 2.0f;
        case ESM::MagicEffect::ResistFire:               return 2.0f;
        case ESM::MagicEffect::ResistFrost:              return 2.0f;
        case ESM::MagicEffect::ResistShock:              return 2.0f;
        case ESM::MagicEffect::ResistMagicka:            return 2.0f;
        case ESM::MagicEffect::ResistCommonDisease:      return 2.0f;
        case ESM::MagicEffect::ResistBlightDisease:      return 5.0f;
        case ESM::MagicEffect::ResistCorprusDisease:     return 5.0f;
        case ESM::MagicEffect::ResistPoison:             return 2.0f;
        case ESM::MagicEffect::ResistNormalWeapons:      return 5.0f;
        case ESM::MagicEffect::ResistParalysis:          return 0.2f;
        case ESM::MagicEffect::RemoveCurse:              return 15.0f;
        case ESM::MagicEffect::TurnUndead:                return 0.2f;
        case ESM::MagicEffect::SummonScamp:               return 12.0f;
        case ESM::MagicEffect::SummonClannfear:           return 22.0f;
        case ESM::MagicEffect::SummonDaedroth:            return 32.0f;
        case ESM::MagicEffect::SummonDremora:             return 28.0f;
        case ESM::MagicEffect::SummonAncestralGhost:      return 7.0f;
        case ESM::MagicEffect::SummonSkeletalMinion:      return 13.0f;
        case ESM::MagicEffect::SummonBonewalker:          return 13.0f;
        case ESM::MagicEffect::SummonGreaterBonewalker:   return 15.0f;
        case ESM::MagicEffect::SummonBonelord:            return 25.0f;
        case ESM::MagicEffect::SummonWingedTwilight:      return 52.0f;
        case ESM::MagicEffect::SummonHunger:              return 29.0f;
        case ESM::MagicEffect::SummonGoldenSaint:         return 55.0f;
        case ESM::MagicEffect::SummonFlameAtronach:       return 23.0f;
        case ESM::MagicEffect::SummonFrostAtronach:       return 27.0f;
        case ESM::MagicEffect::SummonStormAtronach:       return 38.0f;
        case ESM::MagicEffect::FortifyAttack:             return 1.0f;
        case ESM::MagicEffect::CommandCreature:           return 15.0f;
        case ESM::MagicEffect::CommandHumanoid:           return 15.0f;
        case ESM::MagicEffect::BoundDagger:               return 2.0f;
        case ESM::MagicEffect::BoundLongsword:            return 2.0f;
        case ESM::MagicEffect::BoundMace:                 return 2.0f;
        case ESM::MagicEffect::BoundBattleAxe:            return 2.0f;
        case ESM::MagicEffect::BoundSpear:                return 2.0f;
        case ESM::MagicEffect::BoundLongbow:              return 2.0f;
        case ESM::MagicEffect::ExtraSpell:                return 0.0f;
        case ESM::MagicEffect::BoundCuirass:              return 2.0f;
        case ESM::MagicEffect::BoundHelm:                 return 2.0f;
        case ESM::MagicEffect::BoundBoots:                return 2.0f;
        case ESM::MagicEffect::BoundShield:               return 2.0f;
        case ESM::MagicEffect::BoundGloves:               return 2.0f;
        case ESM::MagicEffect::Corprus:                   return 2500.0f;
        case ESM::MagicEffect::Vampirism:                 return 5.0f;
        case ESM::MagicEffect::SummonCenturionSphere:     return 25.0f;
        case ESM::MagicEffect::SunDamage:                 return 1.0f;
        case ESM::MagicEffect::StuntedMagicka:            return 1.0f;
        case ESM::MagicEffect::SummonFabricant:           return 10.0f;
        case ESM::MagicEffect::SummonWolf:                return 30.0f;
        case ESM::MagicEffect::SummonBear:                return 30.0f;
        case ESM::MagicEffect::SummonBonewolf:            return 30.0f;
        case ESM::MagicEffect::SummonCreature04:          return 0.0f;
        case ESM::MagicEffect::SummonCreature05:          return 0.0f;

        default:
            return 1.0f;
        }
    }

    float calcSpellBaseSuccessChance (const ESM::Spell* spell, const MWWorld::Ptr& actor, int* effectiveSchool)
    {
        // Morrowind for some reason uses a formula slightly different from magicka cost calculation
        float y = std::numeric_limits<float>::max();
        float lowestSkill = 0;
        MWWorld::Ptr player = MWMechanics::getPlayer();

        for (const ESM::ENAMstruct& effect : spell->mEffects.mList)
        {
            float x = static_cast<float>(effect.mDuration);
            const auto magicEffect = MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find(effect.mEffectID);

            if (!(magicEffect->mData.mFlags & ESM::MagicEffect::AppliedOnce))
                x = std::max(1.f, x);

            float effectCost = 1.0f;

            if (actor != player)
            {
                // NPC logic forks into the getBaseGameEffectCost function which manually defines all base game effect values
                effectCost = getBaseGameEffectCost(effect.mEffectID);
            }
            else
            {
                effectCost = magicEffect->mData.mBaseCost;
            }
            
            x *= 0.1f * effectCost;
            x *= 0.5f * (effect.mMagnMin + effect.mMagnMax);
            x += effect.mArea * 0.05f * effectCost;
            if (effect.mRange == ESM::RT_Target)
                x *= 1.5f;
            static const float fEffectCostMult = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find(
                        "fEffectCostMult")->mValue.getFloat();
            x *= fEffectCostMult;

            float s = 2.0f * actor.getClass().getSkill(actor, spellSchoolToSkill(magicEffect->mData.mSchool));
            if (s - x < y)
            {
                y = s - x;
                if (effectiveSchool)
                    *effectiveSchool = magicEffect->mData.mSchool;
                lowestSkill = s;
            }
        }

        CreatureStats& stats = actor.getClass().getCreatureStats(actor);

        float actorWillpower = stats.getAttribute(ESM::Attribute::Willpower).getModified();
        float actorLuck = stats.getAttribute(ESM::Attribute::Luck).getModified();

        if (actor == player)
        {
            actorWillpower *= 1.5f;
        }

        float castChance = (lowestSkill - spell->mData.mCost + 0.2f * actorWillpower + 0.1f * actorLuck);

        return castChance;
    }

    float getSpellSuccessChance (const ESM::Spell* spell, const MWWorld::Ptr& actor, int* effectiveSchool, bool cap, bool checkMagicka)
    {
        // NB: Base chance is calculated here because the effective school pointer must be filled
        float baseChance = calcSpellBaseSuccessChance(spell, actor, effectiveSchool);

        bool godmode = actor == getPlayer() && MWBase::Environment::get().getWorld()->getGodModeState();

        CreatureStats& stats = actor.getClass().getCreatureStats(actor);

        if (stats.getMagicEffects().get(ESM::MagicEffect::Silence).getMagnitude() && !godmode)
            return 0;

        if (spell->mData.mType == ESM::Spell::ST_Power)
            return stats.getSpells().canUsePower(spell) ? 100 : 0;

        if (godmode)
            return 100;

        if (spell->mData.mType != ESM::Spell::ST_Spell)
            return 100;

        if (checkMagicka && spell->mData.mCost > 0 && stats.getMagicka().getCurrent() < spell->mData.mCost)
            return 0;

        if (spell->mData.mFlags & ESM::Spell::F_Always)
            return 100;

        float castBonus = -stats.getMagicEffects().get(ESM::MagicEffect::Sound).getMagnitude();
        float castChance = baseChance + castBonus;
        castChance *= stats.getFatigueTerm();

        return std::max(0.f, cap ? std::min(100.f, castChance) : castChance);
    }

    float getSpellSuccessChance (const std::string& spellId, const MWWorld::Ptr& actor, int* effectiveSchool, bool cap, bool checkMagicka)
    {
        if (const auto spell = MWBase::Environment::get().getWorld()->getStore().get<ESM::Spell>().search(spellId))
            return getSpellSuccessChance(spell, actor, effectiveSchool, cap, checkMagicka);
        return 0.f;
    }

    int getSpellSchool(const std::string& spellId, const MWWorld::Ptr& actor)
    {
        int school = 0;
        getSpellSuccessChance(spellId, actor, &school);
        return school;
    }

    int getSpellSchool(const ESM::Spell* spell, const MWWorld::Ptr& actor)
    {
        int school = 0;
        getSpellSuccessChance(spell, actor, &school);
        return school;
    }

    bool spellIncreasesSkill(const ESM::Spell *spell)
    {
        return spell->mData.mType == ESM::Spell::ST_Spell && !(spell->mData.mFlags & ESM::Spell::F_Always);
    }

    bool spellIncreasesSkill(const std::string &spellId)
    {
        const auto spell = MWBase::Environment::get().getWorld()->getStore().get<ESM::Spell>().search(spellId);
        return spell && spellIncreasesSkill(spell);
    }

    bool checkEffectTarget (int effectId, const MWWorld::Ptr& target, const MWWorld::Ptr& caster, bool castByPlayer)
    {
        switch (effectId)
        {
            case ESM::MagicEffect::Levitate:
            {
                if (!MWBase::Environment::get().getWorld()->isLevitationEnabled())
                {
                    if (castByPlayer)
                        MWBase::Environment::get().getWindowManager()->messageBox("#{sLevitateDisabled}");
                    return false;
                }
                break;
            }
            case ESM::MagicEffect::Soultrap:
            {
                if (!target.getClass().isNpc() // no messagebox for NPCs
                     && (target.getTypeName() == typeid(ESM::Creature).name() && target.get<ESM::Creature>()->mBase->mData.mSoul == 0))
                {
                    if (castByPlayer)
                        MWBase::Environment::get().getWindowManager()->messageBox("#{sMagicInvalidTarget}");
                    return true; // must still apply to get visual effect and have target regard it as attack
                }
                break;
            }
            case ESM::MagicEffect::WaterWalking:
            {
                if (target.getClass().isPureWaterCreature(target) && MWBase::Environment::get().getWorld()->isSwimming(target))
                    return false;

                MWBase::World *world = MWBase::Environment::get().getWorld();

                if (!world->isWaterWalkingCastableOnTarget(target))
                {
                    if (castByPlayer && caster == target)
                        MWBase::Environment::get().getWindowManager()->messageBox ("#{sMagicInvalidEffect}");
                    return false;
                }
                break;
            }
        }
        return true;
    }
}
