#include <components/openmw-mp/NetworkMessages.hpp>
#include <PacketPriority.h>
#include <RakPeer.h>
#include "BasePacket.hpp"

using namespace mwmp;

BasePacket::BasePacket(RakNet::RakPeerInterface *peer)
{
    packetID = 0;
    priority = HIGH_PRIORITY;
    reliability = RELIABLE_ORDERED;
    orderChannel = CHANNEL_SYSTEM;
    this->peer = peer;
}

void BasePacket::Packet(RakNet::BitStream *newBitstream, bool send)
{
    bs = newBitstream;
    packetValid = true;

    if (send)
    {
        bs->Write(packetID);
        bs->Write(guid);
    }
}

void BasePacket::SetReadStream(RakNet::BitStream *bitStream)
{
    bsRead = bitStream;
}

void BasePacket::SetSendStream(RakNet::BitStream *bitStream)
{
    bsSend = bitStream;
}

void BasePacket::SetStreams(RakNet::BitStream *inStream, RakNet::BitStream *outStream)
{
    if (inStream != nullptr)
        bsRead = inStream;
    if (outStream != nullptr)
        bsSend = outStream;
}

uint32_t BasePacket::RequestData(RakNet::RakNetGUID targetGuid)
{
    bsSend->ResetWritePointer();
    bsSend->Write(packetID);
    bsSend->Write(targetGuid);
    return peer->Send(bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, orderChannel, targetGuid, false);
}

uint32_t BasePacket::Send(RakNet::AddressOrGUID destination)
{
    bsSend->ResetWritePointer();
    Packet(bsSend, true);
    return peer->Send(bsSend, priority, reliability, orderChannel, destination, false);
}

uint32_t BasePacket::Send(bool toOther)
{
    bsSend->ResetWritePointer();
    Packet(bsSend, true);
    return peer->Send(bsSend, priority, reliability, orderChannel, guid, toOther);
}

void BasePacket::Read()
{
    Packet(bsRead, false);
}

void BasePacket::setGUID(RakNet::RakNetGUID newGuid)
{
    guid = newGuid;
}

RakNet::RakNetGUID BasePacket::getGUID()
{
    return guid;
}
