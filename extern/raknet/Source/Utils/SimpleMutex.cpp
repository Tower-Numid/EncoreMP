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

#include "SimpleMutex.h"
#include "RakAssert.h"

using namespace RakNet;

SimpleMutex::SimpleMutex() //: isInitialized(false)
{
    // Prior implementation of Initializing in Lock() was not threadsafe
    Init();
}

SimpleMutex::~SimpleMutex()
{
#ifdef _WIN32
    DeleteCriticalSection(&criticalSection);
#else
    pthread_mutex_destroy(&hMutex);
#endif
}

#ifdef _WIN32
#ifdef _DEBUG
#include <stdio.h>
#endif
#endif

void SimpleMutex::Lock()
{
#ifdef _WIN32
    EnterCriticalSection(&criticalSection);
#else
    int error = pthread_mutex_lock(&hMutex);
    (void) error;
    RakAssert(error == 0);
#endif
}

void SimpleMutex::Unlock()
{
#ifdef _WIN32
    LeaveCriticalSection(&criticalSection);
#else
    int error = pthread_mutex_unlock(&hMutex);
    RakAssert(error == 0);
#endif
}

void SimpleMutex::Init()
{
#if defined(_WIN32)
    InitializeCriticalSection(&criticalSection);
#else
    int error = pthread_mutex_init(&hMutex, nullptr);
    RakAssert(error == 0);
#endif
//    isInitialized = true;
}
