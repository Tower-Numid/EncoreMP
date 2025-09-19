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

/// \file
///


#include "NetworkIDObject.h"
#include "NetworkIDManager.h"
#include "RakAssert.h"
#include "RakAlloca.h"

using namespace RakNet;

NetworkIDObject::NetworkIDObject()
{
    networkID = UNASSIGNED_NETWORK_ID;
    parent = nullptr;
    networkIDManager = nullptr;
    nextInstanceForNetworkIDManager = nullptr;
}

NetworkIDObject::~NetworkIDObject()
{
    if (networkIDManager != nullptr)
        networkIDManager->StopTrackingNetworkIDObject(this);
}

void NetworkIDObject::SetNetworkIDManager(NetworkIDManager *manager)
{
    if (manager == networkIDManager)
        return;

    if (networkIDManager != nullptr)
        networkIDManager->StopTrackingNetworkIDObject(this);

    networkIDManager = manager;
    if (networkIDManager == nullptr)
    {
        networkID = UNASSIGNED_NETWORK_ID;
        return;
    }

    if (networkID == UNASSIGNED_NETWORK_ID)
    {
        // Prior ID not set
        networkID = networkIDManager->GetNewNetworkID();
    }

    networkIDManager->TrackNetworkIDObject(this);
}

NetworkIDManager *NetworkIDObject::GetNetworkIDManager() const
{
    return networkIDManager;
}

NetworkID NetworkIDObject::GetNetworkID()
{
    return networkID;
}

void NetworkIDObject::SetNetworkID(NetworkID id)
{
    if (networkID == id)
        return;

    if (id == UNASSIGNED_NETWORK_ID)
    {
        SetNetworkIDManager(nullptr);
        return;
    }

    if (networkIDManager != nullptr)
        networkIDManager->StopTrackingNetworkIDObject(this);

    networkID = id;

    if (networkIDManager != nullptr)
        networkIDManager->TrackNetworkIDObject(this);
}

void NetworkIDObject::SetParent(void *_parent)
{
    parent = _parent;
}

void *NetworkIDObject::GetParent() const
{
    return parent;
}
