#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketActorList.hpp"

using namespace mwmp;

PacketActorList::PacketActorList(RakNet::RakPeerInterface *peer) : ActorPacket(peer)
{
    packetID = ID_ACTOR_LIST;
}

void PacketActorList::Packet(RakNet::BitStream *newBitstream, bool send)
{
    if (!ActorPacket::PacketHeader(newBitstream, send))
        return;

    RW(actorList->action, send);

    BaseActor actor;

    for (unsigned int i = 0; i < actorList->count; i++)
    {
        if (send)
            actor = actorList->baseActors.at(i);

        RW(actor.refId, send);
        RW(actor.refNum, send);
        RW(actor.mpNum, send);

        if (actor.refId.empty() || (actor.refNum != 0 && actor.mpNum != 0))
        {
            actorList->isValid = false;
            return;
        }

        if (!send)
            actorList->baseActors.push_back(actor);
    }
}
