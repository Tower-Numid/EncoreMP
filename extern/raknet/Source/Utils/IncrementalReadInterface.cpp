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

#include "IncrementalReadInterface.h"
#include <stdio.h>

using namespace RakNet;

unsigned int IncrementalReadInterface::GetFilePart(const char *filename, unsigned int startReadBytes,
                                                   unsigned int numBytesToRead, void *preallocatedDestination,
                                                   FileListNodeContext &/*context*/)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == nullptr)
        return 0;
    fseek(fp, startReadBytes, SEEK_SET);
    auto numRead = (unsigned int) fread(preallocatedDestination, 1, numBytesToRead, fp);
    fclose(fp);
    return numRead;
}
