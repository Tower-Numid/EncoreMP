#ifndef OPENMW_PACKETPLAYERATTACK_HPP
#define OPENMW_PACKETPLAYERATTACK_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerAttack : public PlayerPacket
    {
    public:
        PacketPlayerAttack(RakNet::RakPeerInterface *peer);

        virtual void Packet(RakNet::BitStream *newBitstream, bool send);
    };
}

#endif //OPENMW_PACKETPLAYERATTACK_HPP
