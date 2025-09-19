#include "PacketPlayerSpellsActive.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketPlayerSpellsActive::PacketPlayerSpellsActive(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_SPELLS_ACTIVE;
}

void PacketPlayerSpellsActive::Packet(RakNet::BitStream *newBitstream, bool send)
{
    PlayerPacket::Packet(newBitstream, send);

    RW(player->spellsActiveChanges.action, send);

    uint32_t count;

    if (send)
        count = static_cast<uint32_t>(player->spellsActiveChanges.activeSpells.size());

    RW(count, send);

    if (!send)
    {
        player->spellsActiveChanges.activeSpells.clear();
        player->spellsActiveChanges.activeSpells.resize(count);
    }

    for (auto&& activeSpell : player->spellsActiveChanges.activeSpells)
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
