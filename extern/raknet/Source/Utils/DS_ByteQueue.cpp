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

#include "DS_ByteQueue.h"
#include "RakAssert.h"
#include <cstring> // Memmove
#include <cstdlib> // realloc
#include <cstdio>


using namespace DataStructures;

ByteQueue::ByteQueue()
{
    readOffset = writeOffset = lengthAllocated = 0;
    data = nullptr;
}
ByteQueue::~ByteQueue()
{
    Clear();


}
void ByteQueue::WriteBytes(const char *in, unsigned length)
{
    unsigned bytesWritten = GetBytesWritten();
    if (lengthAllocated==0 || length > lengthAllocated - bytesWritten - 1)
    {
        unsigned oldLengthAllocated = lengthAllocated;
        // Always need to waste 1 byte for the math to work, else writeoffset==readoffset
        unsigned newAmountToAllocate = length + oldLengthAllocated + 1;
        if (newAmountToAllocate < 256)
            newAmountToAllocate = 256;
        lengthAllocated = lengthAllocated + newAmountToAllocate;
        auto tmp = (char*) realloc(data, lengthAllocated);
        RakAssert(tmp);
        data = tmp;
        if (writeOffset < readOffset)
        {
            if (writeOffset <= newAmountToAllocate)
            {
                memcpy(data + oldLengthAllocated, data, writeOffset);
                writeOffset = readOffset + bytesWritten;
            }
            else
            {
                memcpy(data + oldLengthAllocated, data, newAmountToAllocate);
                memmove(data, data+newAmountToAllocate, writeOffset - newAmountToAllocate);
                writeOffset -= newAmountToAllocate;
            }
        }
    }

    if (length <= lengthAllocated - writeOffset)
        memcpy(data + writeOffset, in, length);
    else
    {
        // Wrap
        memcpy(data + writeOffset, in, lengthAllocated - writeOffset);
        memcpy(data, in + (lengthAllocated - writeOffset), length - (lengthAllocated - writeOffset));
    }
    writeOffset=(writeOffset+length) % lengthAllocated;
}
bool ByteQueue::ReadBytes(char *out, unsigned maxLengthToRead, bool peek)
{
    unsigned bytesWritten = GetBytesWritten();
    unsigned bytesToRead = bytesWritten < maxLengthToRead ? bytesWritten : maxLengthToRead;
    if (bytesToRead == 0)
        return false;
    if (writeOffset >= readOffset)
    {
        memcpy(out, data + readOffset, bytesToRead);
    }
    else
    {
        unsigned availableUntilWrap = lengthAllocated-readOffset;
        if (bytesToRead <= availableUntilWrap)
        {
            memcpy(out, data + readOffset, bytesToRead);
        }
        else
        {
            memcpy(out, data+readOffset, availableUntilWrap);
            memcpy(out + availableUntilWrap, data, bytesToRead - availableUntilWrap);
        }
    }

    if (!peek)
        IncrementReadOffset(bytesToRead);

    return true;
}
char* ByteQueue::PeekContiguousBytes(unsigned int *outLength) const
{
    if (writeOffset >= readOffset)
        *outLength=writeOffset - readOffset;
    else
        *outLength=lengthAllocated - readOffset;
    return data + readOffset;
}
void ByteQueue::Clear()
{
    if (lengthAllocated)
        free(data);
    readOffset = writeOffset=lengthAllocated=0;
    data = nullptr;
}
unsigned ByteQueue::GetBytesWritten() const
{
    if (writeOffset >= readOffset)
        return writeOffset - readOffset;
    else
        return writeOffset + (lengthAllocated - readOffset);
}
void ByteQueue::IncrementReadOffset(unsigned length)
{
    readOffset = (readOffset + length) % lengthAllocated;
}
void ByteQueue::DecrementReadOffset(unsigned length)
{
    if (length > readOffset)
        readOffset = lengthAllocated - (length - readOffset);
    else
        readOffset -= length;
}
void ByteQueue::Print()
{
    for (unsigned i= readOffset; i != writeOffset; i++)
        CRABNET_DEBUG_PRINTF("%i ", data[i]);
    CRABNET_DEBUG_PRINTF("\n");
}
