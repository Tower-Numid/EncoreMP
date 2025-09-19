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

#include "EpochTimeToString.h"
#include <cstdio>
#include <ctime>

char *EpochTimeToString(long long time)
{
    static char text[64];

    struct tm *timeinfo;
    time_t t = time;
    timeinfo = localtime(&t);
    strftime(text, 64, "%c.", timeinfo);

    return text;
}
