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
#if _CRABNET_SUPPORT_LogCommandParser==1 && _CRABNET_SUPPORT_PacketLogger==1
#include "PacketConsoleLogger.h"
#include "LogCommandParser.h"
#include <stdio.h>

using namespace RakNet;

PacketConsoleLogger::PacketConsoleLogger()
{
    logCommandParser=0;
}

void PacketConsoleLogger::SetLogCommandParser(LogCommandParser *lcp)
{
    logCommandParser=lcp;
    if (logCommandParser)
        logCommandParser->AddChannel("PacketConsoleLogger");
}
void PacketConsoleLogger::WriteLog(const char *str)
{
    if (logCommandParser)
        logCommandParser->WriteLog("PacketConsoleLogger", str);
}

#endif // _CRABNET_SUPPORT_*
