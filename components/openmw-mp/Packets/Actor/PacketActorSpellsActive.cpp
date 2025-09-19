#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/TimedLog.hpp>
#include "PacketActorSpellsActive.hpp"

using namespace mwmp;

PacketActorSpellsActive::PacketActorSpellsActive(RakNet::RakPeerInterface *peer) : ActorPacket(peer)
{
    packetID = ID_ACTOR_SPELLS_ACTIVE;
}

void PacketActorSpellsActive::Actor(BaseActor &actor, bool send)
{
    RW(actor.spellsActiveChanges.action, send);

    uint32_t count;

    if (send)
        count = static_cast<uint32_t>(actor.spellsActiveChanges.activeSpells.size());

    RW(count, send);

    if (!send)
    {
        actor.spellsActiveChanges.activeSpells.clear();
        actor.spellsActiveChanges.activeSpells.resize(count);
    }

    for (auto&& activeSpell : actor.spellsActiveChanges.activeSpells)
    {
        RW(activeSpell.id, send, true);
        RW(activeSpell.isStackingSpell, send);
        RW(activeSpell.timestampDay, send);
        RW(activeSpell.timestampHour, send);
        RW(activeSpell.params.mDisplayName, send, true);

        RW(activeSpell.caster.isPlayer, send);

        if (activeSpell.caster.isPlayer)
        {
            RW(activeSpell.caster.guid, send);
        }
        else
        {
            RW(activeSpell.caster.refId, send, true);
            RW(activeSpell.caster.refNum, send);
            RW(activeSpell.caster.mpNum, send);
        }

        uint32_t effectCount;

        if (send)
            effectCount = static_cast<uint32_t>(activeSpell.params.mEffects.size());

        RW(effectCount, send);

        if (effectCount > maxEffects)
        {
            return;
        }

        if (!send)
        {
            activeSpell.params.mEffects.clear();
            activeSpell.params.mEffects.resize(effectCount);
        }

        for (auto&& effect : activeSpell.params.mEffects)
        {
            RW(effect.mEffectId, send);
            RW(effect.mArg, send);
            RW(effect.mMagnitude, send);
            RW(effect.mDuration, send);
            RW(effect.mTimeLeft, send);
        }
    }
}
