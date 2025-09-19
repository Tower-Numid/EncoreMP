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

/// \file FileOperations.h
///


#include "NativeFeatureIncludes.h"
#if _CRABNET_SUPPORT_FileOperations==1

#ifndef __FILE_OPERATIONS_H
#define __FILE_OPERATIONS_H

#include "Export.h"

bool RAK_DLL_EXPORT WriteFileWithDirectories(const char *path, char *data, unsigned dataLength);
bool RAK_DLL_EXPORT IsSlash(unsigned char c);
void RAK_DLL_EXPORT AddSlash(char *input );
void RAK_DLL_EXPORT QuoteIfSpaces(char *str);
bool RAK_DLL_EXPORT DirectoryExists(const char *directory);
long RAK_DLL_EXPORT GetFileLength(const char *path);

#endif

#endif // _CRABNET_SUPPORT_FileOperations
