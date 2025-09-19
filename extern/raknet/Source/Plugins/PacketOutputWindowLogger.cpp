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

#if defined(UNICODE)
#include "RakWString.h"
#endif

#include "PacketOutputWindowLogger.h"
#include "RakString.h"
#if defined(_WIN32)
#include "WindowsIncludes.h"
#endif

using namespace RakNet;

PacketOutputWindowLogger::PacketOutputWindowLogger()
{
}
PacketOutputWindowLogger::~PacketOutputWindowLogger()
{
}
void PacketOutputWindowLogger::WriteLog(const char *str)
{
#if defined(_WIN32)

    #if defined(UNICODE)
        RakNet::RakWString str2 = str;
        str2+="\n";
        OutputDebugString(str2.C_String());
    #else
        RakNet::RakString str2 = str;
        str2+="\n";
        OutputDebugString(str2.C_String());
    #endif
// DS_APR
#elif defined(__native_client__)
    fprintf(stderr, "%s\n", str);
// /DS_APR
#else
    (void)(str);
#endif
}

#endif // _CRABNET_SUPPORT_*
