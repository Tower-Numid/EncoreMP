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

#include "MiscellaneousTestsTest.h"

/*
Description:
Tests:
virtual void 	SetRouterInterface (RouterInterface *routerInterface)=0
virtual void 	RemoveRouterInterface (RouterInterface *routerInterface)=0
virtual bool 	AdvertiseSystem (const char *host, unsigned short remotePort, const char *data, int dataLength, unsigned connectionSocketIndex=0)=0

Success conditions:

Failure conditions:

RakPeerInterface Functions used, tested indirectly by its use,list may not be complete:
Startup
SetMaximumIncomingConnections
Receive
DeallocatePacket
Send

RakPeerInterface Functions Explicitly Tested:
SetRouterInterface
RemoveRouterInterface
AdvertiseSystem

*/
int MiscellaneousTestsTest::RunTest(DataStructures::List<RakString> params,bool isVerbose,bool noPauses)
{	destroyList.Clear(false);

RakPeerInterface *client,*server;

TestHelpers::StandardClientPrep(client,destroyList);
TestHelpers::StandardServerPrep(server,destroyList);

printf("Testing AdvertiseSystem\n");

client->AdvertiseSystem("127.0.0.1",60000,0,0);

if (!CommonFunctions::WaitForMessageWithID(server,ID_ADVERTISE_SYSTEM,5000))
{

	if (isVerbose)
		DebugTools::ShowError(errorList[1-1],!noPauses && isVerbose,__LINE__,__FILE__);

	return 1;
}

return 0;

}

RakString MiscellaneousTestsTest::GetTestName()
{

	return "MiscellaneousTestsTest";

}

RakString MiscellaneousTestsTest::ErrorCodeToString(int errorCode)
{

	if (errorCode>0&&(unsigned int)errorCode<=errorList.Size())
	{
		return errorList[errorCode-1];
	}
	else
	{
		return "Undefined Error";
	}	

}

void MiscellaneousTestsTest::DestroyPeers()
{

	int theSize=destroyList.Size();

	for (int i=0; i < theSize; i++)
		RakPeerInterface::DestroyInstance(destroyList[i]);

}

MiscellaneousTestsTest::MiscellaneousTestsTest(void)
{

	errorList.Push("Did not recieve client advertise");
	errorList.Push("The router interface should not be called because no send has happened yet");
	errorList.Push("Router failed to trigger on failed directed send");
	errorList.Push("Router was not properly removed");

}

MiscellaneousTestsTest::~MiscellaneousTestsTest(void)
{
}