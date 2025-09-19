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

#include <locale>

#if (defined(__GNUC__) || defined(__ARMCC_VERSION) || defined(__GCCXML__) || defined(__S3E__)) && !defined(_WIN32)

#ifndef __APPLE__

char *_strlwr(char *str)
{
    if (str == nullptr)
        return nullptr;
    for (int i = 0; str[i]; ++i)
        str[i] = static_cast<char>(tolower(str[i]));
    return str;
}

#endif
#endif
