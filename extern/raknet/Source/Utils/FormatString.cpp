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

#include "FormatString.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "LinuxStrings.h"

char *FormatString(char *output, size_t size, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    _vsnprintf(output, size, format, ap);
    va_end(ap);
    return output;
}
