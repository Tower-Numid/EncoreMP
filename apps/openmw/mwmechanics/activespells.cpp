#include "activespells.hpp"

#include <components/misc/rng.hpp>
#include <components/misc/stringops.hpp>

#include <components/esm/loadmgef.hpp>

/*
    Start of tes3mp addition

    Include additional headers for multiplayer purposes
*/
#include "../mwmechanics/actorutil.hpp"
#include "../mwmechanics/creaturestats.hpp"
#include "../mwworld/class.hpp"
#include "../mwmp/Main.hpp"
#include "../mwmp/LocalPlayer.hpp"
#include "../mwmp/CellController.hpp"
#include "../mwmp/MechanicsHelper.hpp"
/*
    End of tes3mp addition
*/

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"

#include "../mwworld/esmstore.hpp"

namespace MWMechanics
{
    void ActiveSpells::update(float duration) const
    {
        bool rebuild = false;

        // Erase no longer active spells and effects
        if (duration > 0)
        {
            TContainer::iterator iter (mSpells.begin());
            while (iter!=mSpells.end())
            {
                if (!timeToExpire (iter))
                {
                    /*
                        Start of tes3mp addition

                        Whenever the local player loses an active spell, send an ID_PLAYER_SPELLS_ACTIVE packet to the server with it

                        Whenever a local actor loses an active spell, send an ID_ACTOR_SPELLS_ACTIVE packet to the server with it
                    */
                    if (this == &MWMechanics::getPlayer().getClass().getCreatureStats(MWMechanics::getPlayer()).getActiveSpells())
                    {
                        mwmp::Main::get().getLocalPlayer()->sendSpellsActiveRemoval(iter->first,
                            MechanicsHelper::isStackingSpell(iter->first), iter->second.mTimeStamp);
                    }
                    else
                    {
                        MWWorld::Ptr actorPtr = MWBase::Environment::get().getWorld()->searchPtrViaActorId(getActorId());

                        if (mwmp::Main::get().getCellController()->isLocalActor(actorPtr))
                            mwmp::Main::get().getCellController()->getLocalActor(actorPtr)->sendSpellsActiveRemoval(iter->first,
                                MechanicsHelper::isStackingSpell(iter->first), iter->second.mTimeStamp);
                    }
                    /*
                        End of tes3mp addition
                    */

                    mSpells.erase (iter++);
                    rebuild = true;
                }
                else
                {
                    bool interrupt = false;
                    std::vector<ActiveEffect>& effects = iter->second.mEffects;
                    for (std::vector<ActiveEffect>::iterator effectIt = effects.begin(); effectIt != effects.end();)
                    {
                        if (effectIt->mTimeLeft <= 0)
                        {
                            rebuild = true;

                            // Note: it we expire a Corprus effect, we should remove the whole spell.
                            if (effectIt->mEffectId == ESM::MagicEffect::Corprus)
                            {
                                iter = mSpells.erase (iter);
                                interrupt = true;
                                break;
                            }

                            effectIt = effects.erase(effectIt);
                        }
                        else
                        {
                            effectIt->mTimeLeft -= duration;
                            ++effectIt;
                        }
                    }

                    if (!interrupt)
                        ++iter;
                }
            }
        }

        if (mSpellsChanged)
        {
            mSpellsChanged = false;
            rebuild = true;
        }

        if (rebuild)
            rebuildEffects();
    }

    void ActiveSpells::rebuildEffects() const
    {
        mEffects = MagicEffects();

        for (TIterator iter (begin()); iter!=end(); ++iter)
        {
            const std::vector<ActiveEffect>& effects = iter->second.mEffects;

            for (std::vector<ActiveEffect>::const_iterator effectIt = effects.begin(); effectIt != effects.end(); ++effectIt)
            {
                if (effectIt->mTimeLeft > 0)
                    mEffects.add(MWMechanics::EffectKey(effectIt->mEffectId, effectIt->mArg), MWMechanics::EffectParam(effectIt->mMagnitude));
            }
        }
    }

    ActiveSpells::ActiveSpells()
        : mSpellsChanged (false)
    {}

    const MagicEffects& ActiveSpells::getMagicEffects() const
    {
        update(0.f);
        return mEffects;
    }

    ActiveSpells::TIterator ActiveSpells::begin() const
    {
        return mSpells.begin();
    }

    ActiveSpells::TIterator ActiveSpells::end() const
    {
        return mSpells.end();
    }

    double ActiveSpells::timeToExpire (const TIterator& iterator) const
    {
        const std::vector<ActiveEffect>& effects = iterator->second.mEffects;

        float duration = 0;

        for (std::vector<ActiveEffect>::const_iterator iter (effects.begin());
            iter!=effects.end(); ++iter)
        {
            if (iter->mTimeLeft > duration)
                duration = iter->mTimeLeft;
        }

        if (duration < 0)
            return 0;

        return duration;
    }

    bool ActiveSpells::isSpellActive(const std::string& id) const
    {
        for (TContainer::iterator iter = mSpells.begin(); iter != mSpells.end(); ++iter)
        {
            if (Misc::StringUtils::ciEqual(iter->first, id))
                return true;
        }
        return false;
    }

    const ActiveSpells::TContainer& ActiveSpells::getActiveSpells() const
    {
        return mSpells;
    }

    /*
        Start of tes3mp change (major)

        Add a timestamp argument so spells received from other clients can have the same timestamps they had there,
        as well as a sendPacket argument used to prevent packets from being sent back to the server when we've just
        received them from it
    */
    void ActiveSpells::addSpell(const std::string &id, bool stack, std::vector<ActiveEffect> effects,
                                const std::string &displayName, int casterActorId, MWWorld::TimeStamp timestamp, bool sendPacket)
    /*
        End of tes3mp change (major)
    */
    {
        TContainer::iterator it(mSpells.find(id));

        ActiveSpellParams params;
        params.mEffects = effects;
        params.mDisplayName = displayName;
        params.mCasterActorId = casterActorId;

        /*
            Start of tes3mp addition

            Track the timestamp of this active spell so that, if spells are stacked, the correct one can be removed
        */
        params.mTimeStamp = timestamp;
        /*
            End of tes3mp addition
        */

        if (it == end() || stack)
        {
            mSpells.insert(std::make_pair(id, params));
        }
        else
        {
            // addSpell() is called with effects for a range.
            // but a spell may have effects with different ranges (e.g. Touch & Target)
            // so, if we see new effects for same spell assume additional 
            // spell effects and add to existing effects of spell
            mergeEffects(params.mEffects, it->second.mEffects);
            it->second = params;
        }

        /*
            Start of tes3mp addition

            Whenever a player gains an active spell as a result of gameplay, send an ID_PLAYER_SPELLS_ACTIVE packet
            to the server with it
        */
        if (sendPacket)
        {
            if (this == &MWMechanics::getPlayer().getClass().getCreatureStats(MWMechanics::getPlayer()).getActiveSpells())
            {
                mwmp::Main::get().getLocalPlayer()->sendSpellsActiveAddition(id, stack, params);
            }
            else
            {
                MWWorld::Ptr actorPtr = MWBase::Environment::get().getWorld()->searchPtrViaActorId(getActorId());

                if (mwmp::Main::get().getCellController()->isLocalActor(actorPtr))
                    mwmp::Main::get().getCellController()->getLocalActor(actorPtr)->sendSpellsActiveAddition(id, stack, params);
            }
        }
        /*
            End of tes3mp addition
        */

        mSpellsChanged = true;
    }

    /*
        Start of tes3mp addition

        Declare addSpell() without the timestamp argument and make it call the version with that argument,
        using the current time for the timestamp
    */
    void ActiveSpells::addSpell(const std::string& id, bool stack, std::vector<ActiveEffect> effects,
                                const std::string& displayName, int casterActorId)
    {
        MWWorld::TimeStamp timestamp = MWBase::Environment::get().getWorld()->getTimeStamp();

        addSpell(id, stack, effects, displayName, casterActorId, timestamp);
    }
    /*
        End of tes3mp addition
    */

    void ActiveSpells::mergeEffects(std::vector<ActiveEffect>& addTo, const std::vector<ActiveEffect>& from)
    {
        for (std::vector<ActiveEffect>::const_iterator effect(from.begin()); effect != from.end(); ++effect)
        {
            // if effect is not in addTo, add it
            bool missing = true;
            for (std::vector<ActiveEffect>::const_iterator iter(addTo.begin()); iter != addTo.end(); ++iter)
            {
                if ((effect->mEffectId == iter->mEffectId) && (effect->mArg == iter->mArg))
                {
                    missing = false;
                    break;
                }
            }
            if (missing)
            {
                addTo.push_back(*effect);
            }
        }
    }

    void ActiveSpells::removeEffects(const std::string &id)
    {
        for (TContainer::iterator spell = mSpells.begin(); spell != mSpells.end(); ++spell)
        {
            if (spell->first == id)
            {
                spell->second.mEffects.clear();
                mSpellsChanged = true;
            }
        }
    }

    /*
        Start of tes3mp addition

        Remove the spell with a certain ID and a certain timestamp, useful
        when there are stacked spells with the same ID

        Returns a boolean that indicates whether the corresponding spell was found
    */
    bool ActiveSpells::removeSpellByTimestamp(const std::string& id, MWWorld::TimeStamp timestamp)
    {
        for (TContainer::iterator spell = mSpells.begin(); spell != mSpells.end(); ++spell)
        {
            if (spell->first == id)
            {
                if (spell->second.mTimeStamp == timestamp)
                {
                    spell->second.mEffects.clear();
                    mSpellsChanged = true;
                    return true;
                }
            }
        }

        return false;
    }
    /*
        End of tes3mp addition
    */

    void ActiveSpells::visitEffectSources(EffectSourceVisitor &visitor) const
    {
        for (TContainer::const_iterator it = begin(); it != end(); ++it)
        {
            for (std::vector<ActiveEffect>::const_iterator effectIt = it->second.mEffects.begin();
                 effectIt != it->second.mEffects.end(); ++effectIt)
            {
                std::string name = it->second.mDisplayName;

                float magnitude = effectIt->mMagnitude;
                if (magnitude)
                    visitor.visit(MWMechanics::EffectKey(effectIt->mEffectId, effectIt->mArg), effectIt->mEffectIndex, name, it->first, it->second.mCasterActorId, magnitude, effectIt->mTimeLeft, effectIt->mDuration);
            }
        }
    }

    void ActiveSpells::purgeAll(float chance, bool spellOnly)
    {
        for (TContainer::iterator it = mSpells.begin(); it != mSpells.end(); )
        {
            const std::string spellId = it->first;

            // if spellOnly is true, dispell only spells. Leave potions, enchanted items etc.
            if (spellOnly)
            {
                const ESM::Spell* spell = MWBase::Environment::get().getWorld()->getStore().get<ESM::Spell>().search(spellId);
                if (!spell || spell->mData.mType != ESM::Spell::ST_Spell)
                {
                    ++it;
                    continue;
                }
            }

            if (Misc::Rng::roll0to99() < chance)
                mSpells.erase(it++);
            else
                ++it;
        }
        mSpellsChanged = true;
    }

    void ActiveSpells::purgeEffect(short effectId)
    {
        for (TContainer::iterator it = mSpells.begin(); it != mSpells.end(); ++it)
        {
            for (std::vector<ActiveEffect>::iterator effectIt = it->second.mEffects.begin();
                 effectIt != it->second.mEffects.end();)
            {
                if (effectIt->mEffectId == effectId)
                    effectIt = it->second.mEffects.erase(effectIt);
                else
                    ++effectIt;
            }
        }
        mSpellsChanged = true;
    }

    void ActiveSpells::purgeEffect(short effectId, const std::string& sourceId, int effectIndex)
    {
        for (TContainer::iterator it = mSpells.begin(); it != mSpells.end(); ++it)
        {
            for (std::vector<ActiveEffect>::iterator effectIt = it->second.mEffects.begin();
                 effectIt != it->second.mEffects.end();)
            {
                if (effectIt->mEffectId == effectId && it->first == sourceId && (effectIndex < 0 || effectIndex == effectIt->mEffectIndex))
                    effectIt = it->second.mEffects.erase(effectIt);
                else
                    ++effectIt;
            }
        }
        mSpellsChanged = true;
    }

    void ActiveSpells::purge(int casterActorId)
    {
        for (TContainer::iterator it = mSpells.begin(); it != mSpells.end(); ++it)
        {
            for (std::vector<ActiveEffect>::iterator effectIt = it->second.mEffects.begin();
                 effectIt != it->second.mEffects.end();)
            {
                if (it->second.mCasterActorId == casterActorId)
                    effectIt = it->second.mEffects.erase(effectIt);
                else
                    ++effectIt;
            }
        }
        mSpellsChanged = true;
    }

    /*
        Start of tes3mp addition

        Allow the purging of an effect for a specific arg (attribute or skill)
    */
    void ActiveSpells::purgeEffectByArg(short effectId, int effectArg)
    {
        for (TContainer::iterator it = mSpells.begin(); it != mSpells.end(); ++it)
        {
            for (std::vector<ActiveEffect>::iterator effectIt = it->second.mEffects.begin();
                effectIt != it->second.mEffects.end();)
            {
                if (effectIt->mEffectId == effectId && effectIt->mArg == effectArg)
                    effectIt = it->second.mEffects.erase(effectIt);
                else
                    ++effectIt;
            }
        }
        mSpellsChanged = true;
    }
    /*
        End of tes3mp addition
    */

    /*
        Start of tes3mp addition

        Make it easy to get an effect's duration
    */
    float ActiveSpells::getEffectDuration(short effectId, std::string sourceId)
    {
        for (TContainer::iterator it = mSpells.begin(); it != mSpells.end(); ++it)
        {
            if (sourceId.compare(it->first) == 0)
            {
                for (std::vector<ActiveEffect>::iterator effectIt = it->second.mEffects.begin();
                    effectIt != it->second.mEffects.end(); ++effectIt)
                {
                    if (effectIt->mEffectId == effectId)
                        return effectIt->mDuration;
                }
            }
        }
        return 0.f;
    }
    /*
        End of tes3mp addition
    */

    void ActiveSpells::purgeCorprusDisease()
    {
        for (TContainer::iterator iter = mSpells.begin(); iter!=mSpells.end();)
        {
            bool hasCorprusEffect = false;
            for (std::vector<ActiveEffect>::iterator effectIt = iter->second.mEffects.begin();
                 effectIt != iter->second.mEffects.end();++effectIt)
            {
                if (effectIt->mEffectId == ESM::MagicEffect::Corprus)
                {
                    hasCorprusEffect = true;
                    break;
                }
            }

            if (hasCorprusEffect)
            {
                mSpells.erase(iter++);
                mSpellsChanged = true;
            }
            else
                ++iter;
        }
    }

    void ActiveSpells::clear()
    {
        mSpells.clear();
        mSpellsChanged = true;
    }

    void ActiveSpells::writeState(ESM::ActiveSpells &state) const
    {
        for (TContainer::const_iterator it = mSpells.begin(); it != mSpells.end(); ++it)
        {
            // Stupid copying of almost identical structures. ESM::TimeStamp <-> MWWorld::TimeStamp
            ESM::ActiveSpells::ActiveSpellParams params;
            params.mEffects = it->second.mEffects;
            params.mCasterActorId = it->second.mCasterActorId;
            params.mDisplayName = it->second.mDisplayName;

            state.mSpells.insert (std::make_pair(it->first, params));
        }
    }

    void ActiveSpells::readState(const ESM::ActiveSpells &state)
    {
        for (ESM::ActiveSpells::TContainer::const_iterator it = state.mSpells.begin(); it != state.mSpells.end(); ++it)
        {
            // Stupid copying of almost identical structures. ESM::TimeStamp <-> MWWorld::TimeStamp
            ActiveSpellParams params;
            params.mEffects = it->second.mEffects;
            params.mCasterActorId = it->second.mCasterActorId;
            params.mDisplayName = it->second.mDisplayName;

            mSpells.insert (std::make_pair(it->first, params));
            mSpellsChanged = true;
        }
    }

    /*
        Start of tes3mp addition

        Make it possible to set and get the actorId for these ActiveSpells
    */
    int ActiveSpells::getActorId() const
    {
        return mActorId;
    }

    void ActiveSpells::setActorId(int actorId)
    {
        mActorId = actorId;
    }
    /*
        End of tes3mp addition
    */
}
