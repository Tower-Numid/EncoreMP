#ifndef OPENMW_PACKETDISCONNECT_HPP
#define OPENMW_PACKETDISCONNECT_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>

namespace mwmp
{
    class PacketDisconnect : public PlayerPacket
    {
    public:
        PacketDisconnect(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
        {
            packetID = ID_USER_DISCONNECTED;
            orderChannel = CHANNEL_SYSTEM;
        }
    };
}

#endif //OPENMW_PACKETDISCONNECT_HPP
