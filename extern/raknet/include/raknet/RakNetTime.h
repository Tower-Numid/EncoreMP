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

#ifndef __CRABNET_TIME_H
#define __CRABNET_TIME_H

#include <stdint.h>
#include "RakNetDefines.h"

namespace RakNet {

    // Define __GET_TIME_64BIT if you want to use large types for GetTime (takes more bandwidth when you transmit time though!)
    // You would want to do this if your system is going to run long enough to overflow the millisecond counter (over a month)
    #if __GET_TIME_64BIT==1
    typedef uint64_t Time;
    #else
    typedef uint32_t Time;
    #endif

    typedef uint32_t TimeMS;
    typedef uint64_t TimeUS;

} // namespace RakNet

#endif
