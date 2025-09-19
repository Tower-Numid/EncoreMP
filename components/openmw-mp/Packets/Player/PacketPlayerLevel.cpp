#include "PacketPlayerLevel.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketPlayerLevel::PacketPlayerLevel(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_LEVEL;
}

void PacketPlayerLevel::Packet(RakNet::BitStream *newBitstream, bool send)
{
    PlayerPacket::Packet(newBitstream, send);

    RW(player->creatureStats.mLevel, send);

    RW(player->npcStats.mLevelProgress, send);
}
