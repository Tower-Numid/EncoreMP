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

#include "DS_BytePool.h"
#include "RakAssert.h"
#ifndef __APPLE__
// Use stdlib and not malloc for compatibility
#include <cstdlib>
#endif

using namespace DataStructures;

BytePool::BytePool()
{
    pool128.SetPageSize(8192*4);
    pool512.SetPageSize(8192*4);
    pool2048.SetPageSize(8192*4);
    pool8192.SetPageSize(8192*4);
}

void BytePool::SetPageSize(int size)
{
    pool128.SetPageSize(size);
    pool512.SetPageSize(size);
    pool2048.SetPageSize(size);
    pool8192.SetPageSize(size);
}
unsigned char *BytePool::Allocate(int bytesWanted)
{
#ifdef _DISABLE_BYTE_POOL
    return malloc(bytesWanted);
#endif
    unsigned char *out;
    if (bytesWanted <= 127)
    {
        #ifdef _THREADSAFE_BYTE_POOL
        mutex128.Lock();
        #endif
        out = (unsigned char*) pool128.Allocate();
        #ifdef _THREADSAFE_BYTE_POOL
        mutex128.Unlock();
        #endif
        out[0] = 0;
        return out + 1;
    }
    if (bytesWanted <= 511)
    {
        #ifdef _THREADSAFE_BYTE_POOL
        mutex512.Lock();
        #endif
        out = (unsigned char*) pool512.Allocate();
        #ifdef _THREADSAFE_BYTE_POOL
        mutex512.Unlock();
        #endif
        out[0] = 1;
        return out + 1;
    }
    if (bytesWanted <= 2047)
    {
        #ifdef _THREADSAFE_BYTE_POOL
        mutex2048.Lock();
        #endif
        out = (unsigned char*) pool2048.Allocate();
        #ifdef _THREADSAFE_BYTE_POOL
        mutex2048.Unlock();
        #endif
        out[0]=2;
        return out + 1;
    }
    if (bytesWanted <= 8191)
    {
        #ifdef _THREADSAFE_BYTE_POOL
        mutex8192.Lock();
        #endif
        out = (unsigned char*) pool8192.Allocate();
        #ifdef _THREADSAFE_BYTE_POOL
        mutex8192.Unlock();
        #endif
        out[0]=3;
        return out + 1;
    }

    out = (unsigned char*) malloc(bytesWanted + 1);
    RakAssert(out);
    out[0] = (unsigned char) 255;
    return out + 1;
}
void BytePool::Release(unsigned char *data)
{
#ifdef _DISABLE_BYTE_POOL
    free(data);
#endif
    unsigned char *realData = data-1;
    switch (realData[0])
    {
    case 0:
        #ifdef _THREADSAFE_BYTE_POOL
        mutex128.Lock();
        #endif
        pool128.Release((unsigned char(*)[128]) realData);
        #ifdef _THREADSAFE_BYTE_POOL
        mutex128.Unlock();
        #endif
        break;
    case 1:
        #ifdef _THREADSAFE_BYTE_POOL
        mutex512.Lock();
        #endif
        pool512.Release((unsigned char(*)[512]) realData);
        #ifdef _THREADSAFE_BYTE_POOL
        mutex512.Unlock();
        #endif
        break;
    case 2:
        #ifdef _THREADSAFE_BYTE_POOL
        mutex2048.Lock();
        #endif
        pool2048.Release((unsigned char(*)[2048]) realData);
        #ifdef _THREADSAFE_BYTE_POOL
        mutex2048.Unlock();
        #endif
        break;
    case 3:
        #ifdef _THREADSAFE_BYTE_POOL
        mutex8192.Lock();
        #endif
        pool8192.Release((unsigned char(*)[8192]) realData);
        #ifdef _THREADSAFE_BYTE_POOL
        mutex8192.Unlock();
        #endif
        break;
    case 255:
        free(realData);
        break;
    default:
        RakAssert(0);
        break;
    }
}
void BytePool::Clear()
{
#ifdef _THREADSAFE_BYTE_POOL
    pool128.Clear();
    pool512.Clear();
    pool2048.Clear();
    pool8192.Clear();
#endif
}
