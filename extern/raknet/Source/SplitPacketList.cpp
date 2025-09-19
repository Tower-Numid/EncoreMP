//
// Created by koncord on 19.01.18.
//

#include "SplitPacketList.h"
#include <ReliabilityLayer.h>

RakNet::SplitPacketList::SplitPacketList() : splitPacketId(0), inUse(0), reliabilityLayer(nullptr)
{

}

void RakNet::SplitPacketList::prealloc(unsigned count, SplitPacketIdType splitPacketId)
{
    RakAssert(count > 0);
    this->splitPacketId = splitPacketId;
    packets.resize(count);
}

bool RakNet::SplitPacketList::insert(RakNet::InternalPacket *internalPacket)
{
    RakAssert(internalPacket->splitPacketIndex < size());
    RakAssert(splitPacketId == internalPacket->splitPacketId);

    if (packets[internalPacket->splitPacketIndex] == nullptr)
    {
        packets[internalPacket->splitPacketIndex] = internalPacket;
        ++inUse;
        return true;
    }

    // There was an attempt to rewrite packet ptr
    reliabilityLayer->FreeInternalPacketData(internalPacket);
    reliabilityLayer->ReleaseToInternalPacketPool(internalPacket);
    return false;
}

unsigned RakNet::SplitPacketList::size() const
{
    return static_cast<unsigned>(packets.size());
}

unsigned RakNet::SplitPacketList::count() const
{
    return inUse;
}

RakNet::InternalPacket *RakNet::SplitPacketList::operator[](unsigned n)
{
    RakAssert(n < size());
    return packets[n];
}

RakNet::SplitPacketIdType RakNet::SplitPacketList::id() const
{
    return splitPacketId;
}
