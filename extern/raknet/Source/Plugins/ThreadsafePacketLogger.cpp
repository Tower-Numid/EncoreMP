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
#if _CRABNET_SUPPORT_PacketLogger==1

#include "ThreadsafePacketLogger.h"
#include <cstring>
#include <cstdlib>

using namespace RakNet;

ThreadsafePacketLogger::ThreadsafePacketLogger()
{

}
ThreadsafePacketLogger::~ThreadsafePacketLogger()
{
    char **msg;
    while ((msg = logMessages.ReadLock()) != 0)
    {
        free(*msg);
    }
}
void ThreadsafePacketLogger::Update(void)
{
    char **msg;
    while ((msg = logMessages.ReadLock()) != 0)
    {
        WriteLog(*msg);
        free(*msg);
    }
}
void ThreadsafePacketLogger::AddToLog(const char *str)
{
    char **msg = logMessages.WriteLock();
    *msg = (char*) malloc(strlen(str)+1);
    strcpy(*msg, str);
    logMessages.WriteUnlock();
}

#endif // _CRABNET_SUPPORT_*
