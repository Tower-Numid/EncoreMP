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

#ifndef __WSA_STARTUP_SINGLETON_H
#define __WSA_STARTUP_SINGLETON_H

#ifdef _WIN32
class WSAStartupSingleton
{
public:
    WSAStartupSingleton();
    ~WSAStartupSingleton();
    static void AddRef(void);
    static void Deref(void);

protected:
    static int refCount;
};
#endif

#endif
