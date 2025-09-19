/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  Copyright (c) 2016-2018, TES3MP Team
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "NativeFeatureIncludes.h"
#if _CRABNET_SUPPORT_TelnetTransport==1

#include "RakNetTransport2.h"

#include "RakPeerInterface.h"
#include "BitStream.h"
#include "MessageIdentifiers.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "../Utils/LinuxStrings.h"

#ifdef _MSC_VER
#pragma warning( push )
#endif

using namespace RakNet;

STATIC_FACTORY_DEFINITIONS(RakNetTransport2,RakNetTransport2)

RakNetTransport2::RakNetTransport2()
{
}
RakNetTransport2::~RakNetTransport2()
{
    Stop();
}
bool RakNetTransport2::Start(unsigned short port, bool serverMode)
{
    (void) port;
    (void) serverMode;
    return true;
}
void RakNetTransport2::Stop(void)
{
    newConnections.Clear();
    lostConnections.Clear();
    for (unsigned int i=0; i < packetQueue.Size(); i++)
    {
        free(packetQueue[i]->data);
        delete packetQueue[i];
    }
    packetQueue.Clear();
}
void RakNetTransport2::Send( SystemAddress systemAddress, const char *data, ... )
{
    if (data==0 || data[0]==0) return;

    char text[REMOTE_MAX_TEXT_INPUT];
    va_list ap;
    va_start(ap, data);
    _vsnprintf(text, REMOTE_MAX_TEXT_INPUT, data, ap);
    va_end(ap);
    text[REMOTE_MAX_TEXT_INPUT-1]=0;

    RakNet::BitStream str;
    str.Write((MessageID)ID_TRANSPORT_STRING);
    str.Write(text, (int) strlen(text));
    str.Write((unsigned char) 0); // Null terminate the string
    rakPeerInterface->Send(&str, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, systemAddress, (systemAddress==UNASSIGNED_SYSTEM_ADDRESS)!=0);
}
void RakNetTransport2::CloseConnection( SystemAddress systemAddress )
{
    rakPeerInterface->CloseConnection(systemAddress, true, 0);
}
Packet* RakNetTransport2::Receive( void )
{
    if (packetQueue.Size()==0)
        return 0;
    return packetQueue.Pop();
}
SystemAddress RakNetTransport2::HasNewIncomingConnection(void)
{
    if (newConnections.Size())
        return newConnections.Pop();
    return UNASSIGNED_SYSTEM_ADDRESS;
}
SystemAddress RakNetTransport2::HasLostConnection(void)
{
    if (lostConnections.Size())
        return lostConnections.Pop();
    return UNASSIGNED_SYSTEM_ADDRESS;
}
void RakNetTransport2::DeallocatePacket( Packet *packet )
{
    free(packet->data);
    delete packet;
}
PluginReceiveResult RakNetTransport2::OnReceive(Packet *packet)
{
    switch (packet->data[0])
    {
    case ID_TRANSPORT_STRING:
        {
            if (packet->length==sizeof(MessageID))
                return RR_STOP_PROCESSING_AND_DEALLOCATE;

            Packet *p = new Packet;
            *p = *packet;
            p->bitSize -= 8;
            p->length--;
            p->data = (unsigned char *) malloc(p->length);
            RakAssert(p->data)
            memcpy(p->data, packet->data + 1, p->length);
            packetQueue.Push(p);

        }
        return RR_STOP_PROCESSING_AND_DEALLOCATE;
    }
    return RR_CONTINUE_PROCESSING;
}
void RakNetTransport2::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
    (void) rakNetGUID;
    (void) lostConnectionReason;
    lostConnections.Push(systemAddress);
}
void RakNetTransport2::OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming)
{
    (void) rakNetGUID;
    (void) isIncoming;
    newConnections.Push(systemAddress);
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _CRABNET_SUPPORT_*
