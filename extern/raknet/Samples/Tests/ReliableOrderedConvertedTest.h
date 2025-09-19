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

#pragma once


#include "TestInterface.h"


#include "RakPeerInterface.h"
#include "GetTime.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include <cstdio>
#include <memory.h>
#include <cstring>
#include <stdlib.h>
#include "Rand.h"
#include "RakNetStatistics.h"
#include "RakSleep.h"
#include "RakMemoryOverride.h"

#include "DebugTools.h"

using namespace RakNet;
class ReliableOrderedConvertedTest : public TestInterface
{
public:
	ReliableOrderedConvertedTest(void);
	~ReliableOrderedConvertedTest(void);
	int RunTest(DataStructures::List<RakString> params,bool isVerbose,bool noPauses);//should return 0 if no error, or the error number
	RakString GetTestName();
	RakString ErrorCodeToString(int errorCode);
	void DestroyPeers();
protected:
	void *LoggedMalloc(size_t size);
	void LoggedFree(void *p);
	void* LoggedRealloc(void *p, size_t size);
private:
	DataStructures::List <RakPeerInterface *> destroyList;

};
