#ifndef OPENMW_PACKETPLAYERCELLSTATE_HPP
#define OPENMW_PACKETPLAYERCELLSTATE_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerCellState : public PlayerPacket
    {
    public:
        PacketPlayerCellState(RakNet::RakPeerInterface *peer);

        virtual void Packet(RakNet::BitStream *newBitstream, bool send);
    };
}

#endif //OPENMW_PACKETPLAYERCELLSTATE_HPP
