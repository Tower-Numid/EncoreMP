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

/// \file FormatString.h
///


#ifndef __FORMAT_STRING_H
#define __FORMAT_STRING_H

#include <cstddef>
#include "Export.h"

// Threadsafe
extern "C" {
char *FormatString(char *output, size_t size, const char *format, ...);
}


#endif

