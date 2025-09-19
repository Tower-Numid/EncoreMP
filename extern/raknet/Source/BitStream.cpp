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

/// \file
///

#include "BitStream.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>

#include "SocketIncludes.h"
#include "RakNetDefines.h"

#if defined(_WIN32)
#include "WindowsIncludes.h"
#else

#include <arpa/inet.h>

#endif

#include <memory.h>
#include <cfloat>
#include <algorithm>

// MSWin uses _copysign, others use copysign...
#ifndef _WIN32
#define _copysign copysign
#endif

using namespace RakNet;

#ifdef _MSC_VER
#pragma warning( push )
#endif

STATIC_FACTORY_DEFINITIONS(BitStream, BitStream)

BitStream::BitStream()
{
    numberOfBitsUsed = 0;
    //numberOfBitsAllocated = 32 * 8;
    numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
    readOffset = 0;
    //data = ( unsigned char* ) malloc(( 32);
    data = (unsigned char *) stackData;

    //memset(data, 0, 32);
    copyData = true;
}

BitStream::BitStream(unsigned int initialBytesToAllocate)
{
    numberOfBitsUsed = 0;
    readOffset = 0;
    if (initialBytesToAllocate <= BITSTREAM_STACK_ALLOCATION_SIZE)
    {
        data = (unsigned char *) stackData;
        numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
    }
    else
    {
        data = (unsigned char *) malloc((size_t) initialBytesToAllocate);
        numberOfBitsAllocated = initialBytesToAllocate << 3;
    }

    RakAssert(data);
    // memset(data, 0, initialBytesToAllocate);
    copyData = true;
}

BitStream::BitStream(unsigned char *_data, unsigned int lengthInBytes, bool _copyData)
{
    numberOfBitsUsed = lengthInBytes << 3;
    readOffset = 0;
    copyData = _copyData;
    numberOfBitsAllocated = lengthInBytes << 3;

    if (copyData)
    {
        if (lengthInBytes > 0)
        {
            if (lengthInBytes < BITSTREAM_STACK_ALLOCATION_SIZE)
            {
                data = (unsigned char *) stackData;
                numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE << 3;
            }
            else
                data = (unsigned char *) malloc((size_t) lengthInBytes);

            RakAssert(data);
            memcpy(data, _data, (size_t) lengthInBytes);
        }
        else
            data = nullptr;
    }
    else
        data = _data;
}

// Use this if you pass a pointer copy to the constructor (_copyData==false) and want to overallocate to prevent reallocation
void BitStream::SetNumberOfBitsAllocated(BitSize_t lengthInBits)
{
    RakAssert(lengthInBits >= (BitSize_t) numberOfBitsAllocated);
    numberOfBitsAllocated = lengthInBits;
}

BitStream::~BitStream()
{
    if (copyData && numberOfBitsAllocated > (BITSTREAM_STACK_ALLOCATION_SIZE << 3))
        free(data);  // Use realloc and free so we are more efficient than delete and new for resizing
}

void BitStream::Reset()
{
    // Note:  Do NOT reallocate memory because BitStream is used
    // in places to serialize/deserialize a buffer. Reallocation
    // is a dangerous operation (may result in leaks).

    /*if (numberOfBitsUsed > 0)
        memset(data, 0, BITS_TO_BYTES(numberOfBitsUsed));*/

    // Don't free memory here for speed efficiency
    //free(data);  // Use realloc and free so we are more efficient than delete and new for resizing
    numberOfBitsUsed = 0;

    //numberOfBitsAllocated=8;
    readOffset = 0;

    //data=(unsigned char*)malloc(1);
    // if (numberOfBitsAllocated>0)
    //  memset(data, 0, BITS_TO_BYTES(numberOfBitsAllocated));
}

// Write an array or casted stream
void BitStream::Write(const char *inputByteArray, unsigned int numberOfBytes)
{
    if (numberOfBytes == 0)
        return;

    // Optimization:
    if ((numberOfBitsUsed & 7) == 0)
    {
        AddBitsAndReallocate(BYTES_TO_BITS(numberOfBytes));
        memcpy(data + BITS_TO_BYTES(numberOfBitsUsed), inputByteArray, (size_t) numberOfBytes);
        numberOfBitsUsed += BYTES_TO_BITS(numberOfBytes);
    }
    else
        WriteBits((unsigned char *) inputByteArray, numberOfBytes * 8, true);

}

void BitStream::Write(BitStream *bitStream)
{
    Write(bitStream, bitStream->GetNumberOfBitsUsed() - bitStream->GetReadOffset());
}

void BitStream::Write(BitStream *bitStream, BitSize_t numberOfBits)
{
    AddBitsAndReallocate(numberOfBits);
    BitSize_t numberOfBitsMod8;

    if ((bitStream->GetReadOffset() & 7) == 0 && (numberOfBitsUsed & 7) == 0)
    {
        BitSize_t readOffsetBytes = bitStream->GetReadOffset() / 8;
        BitSize_t numBytes = numberOfBits / 8;
        memcpy(data + (numberOfBitsUsed >> 3), bitStream->GetData() + readOffsetBytes, numBytes);
        numberOfBits -= BYTES_TO_BITS(numBytes);
        bitStream->SetReadOffset(BYTES_TO_BITS(numBytes + readOffsetBytes));
        numberOfBitsUsed += BYTES_TO_BITS(numBytes);
    }

    while (numberOfBits-- > 0 && bitStream->readOffset + 1 <= bitStream->numberOfBitsUsed)
    {
        numberOfBitsMod8 = numberOfBitsUsed & 7;
        if (numberOfBitsMod8 == 0)
        {
            // New byte
            if (bitStream->data[bitStream->readOffset >> 3] & (0x80 >> (bitStream->readOffset & 7)))
                data[numberOfBitsUsed >> 3] = 0x80; // Write 1
            else
                data[numberOfBitsUsed >> 3] = 0; // Write 0

        }
        else
        {
            // Existing byte
            if (bitStream->data[bitStream->readOffset >> 3] & (0x80 >> (bitStream->readOffset & 7)))
                data[numberOfBitsUsed >> 3] |= 0x80 >> (numberOfBitsMod8); // Set the bit to 1
            // else 0, do nothing
        }

        bitStream->readOffset++;
        numberOfBitsUsed++;
    }
}

void BitStream::Write(BitStream &bitStream, BitSize_t numberOfBits)
{
    Write(&bitStream, numberOfBits);
}

void BitStream::Write(BitStream &bitStream)
{
    Write(&bitStream);
}

bool BitStream::Read(BitStream *bitStream, BitSize_t numberOfBits)
{
    if (GetNumberOfUnreadBits() < numberOfBits)
        return false;
    bitStream->Write(this, numberOfBits);
    return true;
}

bool BitStream::Read(BitStream *bitStream)
{
    bitStream->Write(this);
    return true;
}

bool BitStream::Read(BitStream &bitStream, BitSize_t numberOfBits)
{
    if (GetNumberOfUnreadBits() < numberOfBits)
        return false;
    bitStream.Write(this, numberOfBits);
    return true;
}

bool BitStream::Read(BitStream &bitStream)
{
    bitStream.Write(this);
    return true;
}

// Read an array or casted stream
bool BitStream::Read(char *outByteArray, unsigned int numberOfBytes)
{
    // Optimization:
    if ((readOffset & 7) == 0)
    {
        if (readOffset + (numberOfBytes << 3) > numberOfBitsUsed)
            return false;

        // Write the data
        memcpy(outByteArray, data + (readOffset >> 3), (size_t) numberOfBytes);

        readOffset += numberOfBytes << 3;
        return true;
    }
    else
        return ReadBits((unsigned char *) outByteArray, numberOfBytes * 8);
}

// Sets the read pointer back to the beginning of your data.
void BitStream::ResetReadPointer()
{
    readOffset = 0;
}

// Sets the write pointer back to the beginning of your data.
void BitStream::ResetWritePointer()
{
    numberOfBitsUsed = 0;
}

// Write a 0
void BitStream::Write0()
{
    AddBitsAndReallocate(1);

    // New bytes need to be zeroed
    if ((numberOfBitsUsed & 7) == 0)
        data[numberOfBitsUsed >> 3] = 0;

    numberOfBitsUsed++;
}

// Write a 1
void BitStream::Write1()
{
    AddBitsAndReallocate(1);

    BitSize_t numberOfBitsMod8 = numberOfBitsUsed & 7;

    if (numberOfBitsMod8 == 0)
        data[numberOfBitsUsed >> 3] = 0x80;
    else
        data[numberOfBitsUsed >> 3] |= 0x80 >> (numberOfBitsMod8); // Set the bit to 1

    numberOfBitsUsed++;
}

// Returns true if the next data read is a 1, false if it is a 0
bool BitStream::ReadBit()
{
    bool result = (data[readOffset >> 3] & (0x80 >> (readOffset & 7))) != 0;
    readOffset++;
    return result;
}

// Align the bitstream to the byte boundary and then write the specified number of bits.
// This is faster than WriteBits but wastes the bits to do the alignment and requires you to call
// SetReadToByteAlignment at the corresponding read position
void BitStream::WriteAlignedBytes(const uint8_t *inByteArray, unsigned int numberOfBytesToWrite)
{
    AlignWriteToByteBoundary();
    Write((const char *) inByteArray, numberOfBytesToWrite);
}

void BitStream::EndianSwapBytes(int byteOffset, unsigned int length)
{
    if (DoEndianSwap())
        ReverseBytesInPlace(data + byteOffset, length);
}

/// Aligns the bitstream, writes inputLength, and writes input. Won't write beyond maxBytesToWrite
void BitStream::WriteAlignedBytesSafe(const char *inByteArray, unsigned int inputLength, unsigned int maxBytesToWrite)
{
    if (inByteArray == nullptr || inputLength == 0)
    {
        WriteCompressed((unsigned int) 0);
        return;
    }
    WriteCompressed(inputLength);
    WriteAlignedBytes((const unsigned char *) inByteArray, inputLength < maxBytesToWrite ? inputLength : maxBytesToWrite);
}

// Read bits, starting at the next aligned bits. Note that the modulus 8 starting offset of the
// sequence must be the same as was used with WriteBits. This will be a problem with packet coalescence
// unless you byte align the coalesced packets.
bool BitStream::ReadAlignedBytes(unsigned char *inOutByteArray, unsigned int numberOfBytesToRead)
{
    RakAssert(numberOfBytesToRead > 0);

    if (numberOfBytesToRead <= 0)
        return false;

    // Byte align
    AlignReadToByteBoundary();

    if (readOffset + (numberOfBytesToRead << 3) > numberOfBitsUsed)
        return false;

    // Write the data
    memcpy(inOutByteArray, data + (readOffset >> 3), (size_t) numberOfBytesToRead);

    readOffset += numberOfBytesToRead << 3;

    return true;
}

bool BitStream::ReadAlignedBytesSafe(char *inOutByteArray, unsigned int &inputLength, unsigned int maxBytesToRead)
{
    if (!ReadCompressed(inputLength))
        return false;
    if (inputLength > maxBytesToRead)
        inputLength = maxBytesToRead;
    if (inputLength == 0)
        return true;
    return ReadAlignedBytes((unsigned char *) inOutByteArray, inputLength);
}

bool BitStream::ReadAlignedBytesSafeAlloc(char **outByteArray, unsigned int &inputLength, unsigned int maxBytesToRead)
{
    free(*outByteArray);
    *outByteArray = nullptr;
    if (!ReadCompressed(inputLength))
        return false;
    if (inputLength > maxBytesToRead)
        inputLength = maxBytesToRead;
    if (inputLength == 0)
        return true;
    *outByteArray = (char *) malloc((size_t) inputLength);
    return ReadAlignedBytes((unsigned char *) *outByteArray, inputLength);
}

// Write numberToWrite bits from the input source
void BitStream::WriteBits(const unsigned char *inByteArray, BitSize_t numberOfBitsToWrite, bool rightAlignedBits)
{
//    if (numberOfBitsToWrite<=0)
//        return;
    AddBitsAndReallocate(numberOfBitsToWrite);

    const BitSize_t numberOfBitsUsedMod8 = numberOfBitsUsed & 7;

    // If currently aligned and numberOfBits is a multiple of 8, just memcpy for speed
    if (numberOfBitsUsedMod8 == 0 && (numberOfBitsToWrite & 7) == 0)
    {
        memcpy(data + (numberOfBitsUsed >> 3), inByteArray, numberOfBitsToWrite >> 3);
        numberOfBitsUsed += numberOfBitsToWrite;
        return;
    }

    const unsigned char *inputPtr = inByteArray;

    // Faster to put the while at the top surprisingly enough
    while (numberOfBitsToWrite > 0)
    {
        unsigned char dataByte = *(inputPtr++);

        // rightAlignedBits means in the case of a partial byte, the bits are aligned from the right (bit 0) rather than
        // the left (as in the normal internal representation)
        if (numberOfBitsToWrite < 8 && rightAlignedBits)
            dataByte <<= 8 - numberOfBitsToWrite;  // shift left to get the bits on the left, as in our internal representation

        // Writing to a new byte each time
        if (numberOfBitsUsedMod8 == 0) *(data + (numberOfBitsUsed >> 3)) = dataByte;
        else
        {
            // Copy over the new data.
            *(data + (numberOfBitsUsed >> 3)) |= dataByte >> (numberOfBitsUsedMod8); // First half

            // If we didn't write it all out in the first half (8 - (numberOfBitsUsed%8) is the number we wrote in the first half)
            if (8 - (numberOfBitsUsedMod8) < 8 && 8 - (numberOfBitsUsedMod8) < numberOfBitsToWrite)
            {
                // Second half (overlaps byte boundary)
                *(data + (numberOfBitsUsed >> 3) + 1) = dataByte << (8 - (numberOfBitsUsedMod8));
            }
        }

        if (numberOfBitsToWrite >= 8)
        {
            numberOfBitsUsed += 8;
            numberOfBitsToWrite -= 8;
        }
        else
        {
            numberOfBitsUsed += numberOfBitsToWrite;
            numberOfBitsToWrite = 0;
        }
    }
}

// Set the stream to some initial data.  For internal use
void BitStream::SetData(unsigned char *inByteArray)
{
    data = inByteArray;
    copyData = false;
}

// Assume the input source points to a native type, compress and write it
void BitStream::WriteCompressed(const unsigned char *inByteArray, unsigned int size, bool unsignedData)
{
    BitSize_t currentByte = (size >> 3) - 1; // PCs

    unsigned char byteMatch;

    if (unsignedData)
        byteMatch = 0;
    else
        byteMatch = 0xFF;

    // Write upper bytes with a single 1
    // From high byte to low byte, if high byte is a byteMatch then write a 1 bit.
    // Otherwise write a 0 bit and then write the remaining bytes
    while (currentByte > 0)
    {
        // If high byte is byteMatch (0 of 0xff) then it would have the same value shifted
        if (inByteArray[currentByte] == byteMatch)
            Write(true);
        else
        {
            // Write the remainder of the data after writing 0
            Write(false);

            WriteBits(inByteArray, (currentByte + 1) << 3, true);
            return;
        }
        currentByte--;
    }

    // If the upper half of the last byte is a 0 (positive) or 16 (negative) then write a 1 and the remaining 4 bits.
    // Otherwise write a 0 and the 8 bites.
    if ((unsignedData && ((*(inByteArray + currentByte)) & 0xF0) == 0x00) ||
        (!unsignedData && ((*(inByteArray + currentByte)) & 0xF0) == 0xF0))
    {
        Write(true);
        WriteBits(inByteArray + currentByte, 4, true);
    }
    else
    {
        Write(false);
        WriteBits(inByteArray + currentByte, 8, true);
    }
}

// Read numberOfBitsToRead bits to the output source
// alignBitsToRight should be set to true to convert internal bitstream data to userdata
// It should be false if you used WriteBits with rightAlignedBits false
bool BitStream::ReadBits(unsigned char *inOutByteArray, BitSize_t numberOfBitsToRead, bool alignBitsToRight)
{
    if (numberOfBitsToRead <= 0)
        return false;

    if (readOffset + numberOfBitsToRead > numberOfBitsUsed)
        return false;

    const BitSize_t readOffsetMod8 = readOffset & 7;

    // If currently aligned and numberOfBits is a multiple of 8, just memcpy for speed
    if (readOffsetMod8 == 0 && (numberOfBitsToRead & 7) == 0)
    {
        memcpy(inOutByteArray, data + (readOffset >> 3), numberOfBitsToRead >> 3);
        readOffset += numberOfBitsToRead;
        return true;
    }

    BitSize_t offset = 0;

    memset(inOutByteArray, 0, (size_t) BITS_TO_BYTES(numberOfBitsToRead));

    while (numberOfBitsToRead > 0)
    {
        *(inOutByteArray + offset) |= *(data + (readOffset >> 3)) << (readOffsetMod8); // First half

        // If we have a second half, we didn't read enough bytes in the first half
        if (readOffsetMod8 > 0 && numberOfBitsToRead > 8 - (readOffsetMod8))
            *(inOutByteArray + offset) |= *(data + (readOffset >> 3) + 1) >> (8 - (readOffsetMod8)); // Second half (overlaps byte boundary)

        if (numberOfBitsToRead >= 8)
        {
            numberOfBitsToRead -= 8;
            readOffset += 8;
            offset++;
        }
        else
        {
            int neg = (int) numberOfBitsToRead - 8;

            if (neg < 0)   // Reading a partial byte for the last byte, shift right so the data is aligned on the right
            {

                if (alignBitsToRight)
                    *(inOutByteArray + offset) >>= -neg;

                readOffset += 8 + neg;
            }
            else
                readOffset += 8;

            offset++;

            numberOfBitsToRead = 0;
        }
    }

    return true;
}

// Assume the input source points to a compressed native type. Decompress and read it
bool BitStream::ReadCompressed(unsigned char *inOutByteArray, unsigned int size, bool unsignedData)
{
    unsigned char byteMatch, halfByteMatch;

    if (unsignedData)
    {
        byteMatch = 0;
        halfByteMatch = 0;
    }

    else
    {
        byteMatch = 0xFF;
        halfByteMatch = 0xF0;
    }

    // Upper bytes are specified with a single 1 if they match byteMatch
    // From high byte to low byte, if high byte is a byteMatch then write a 1 bit.
    // Otherwise write a 0 bit and then write the remaining bytes
    unsigned int currentByte = (size >> 3) - 1;
    while (currentByte > 0)
    {
        // If we read a 1 then the data is byteMatch.

        bool b;

        if (!Read(b))
            return false;

        if (b) // Check that bit
        {
            inOutByteArray[currentByte] = byteMatch;
            currentByte--;
        }
        else // Read the rest of the bytes
            return ReadBits(inOutByteArray, (currentByte + 1) << 3);
    }

    // All but the first bytes are byteMatch.  If the upper half of the last byte is a 0 (positive) or 16 (negative)
    // then what we read will be a 1 and the remaining 4 bits.
    // Otherwise we read a 0 and the 8 bytes
    //RakAssert(readOffset+1 <=numberOfBitsUsed); // If this assert is hit the stream wasn't long enough to read from
    if (readOffset + 1 > numberOfBitsUsed)
        return false;

    bool b = false;

    if (!Read(b))
        return false;

    if (b)   // Check that bit
    {

        if (!ReadBits(inOutByteArray + currentByte, 4))
            return false;

        inOutByteArray[currentByte] |= halfByteMatch; // We have to set the high 4 bits since these are set to 0 by ReadBits
    }
    else if (!ReadBits(inOutByteArray + currentByte, 8))
            return false;

    return true;
}

// Reallocates (if necessary) in preparation of writing numberOfBitsToWrite
void BitStream::AddBitsAndReallocate(BitSize_t numberOfBitsToWrite)
{
    BitSize_t newNumberOfBitsAllocated = numberOfBitsToWrite + numberOfBitsUsed;

    // If we need to allocate 1 or more new bytes
    if (numberOfBitsToWrite + numberOfBitsUsed > 0 &&
        ((numberOfBitsAllocated - 1) >> 3) < ((newNumberOfBitsAllocated - 1) >> 3))
    {
        // If this assert hits then we need to specify true for the third parameter in the constructor
        // It needs to reallocate to hold all the data and can't do it unless we allocated to begin with
        // Often hits if you call Write or Serialize on a read-only bitstream
        RakAssert(copyData && " Cannot copy bytes. Set _copyData to \"true\" in constructor.");

        // Less memory efficient but saves on news and deletes
        /// Cap to 1 meg buffer to save on huge allocations
        newNumberOfBitsAllocated = (numberOfBitsToWrite + numberOfBitsUsed) * 2;
        if (newNumberOfBitsAllocated - (numberOfBitsToWrite + numberOfBitsUsed) > 1048576)
            newNumberOfBitsAllocated = numberOfBitsToWrite + numberOfBitsUsed + 1048576;

        // BitSize_t newByteOffset = BITS_TO_BYTES( numberOfBitsAllocated );

        // Use realloc and free so we are more efficient than delete and new for resizing
        BitSize_t amountToAllocate = BITS_TO_BYTES(newNumberOfBitsAllocated);
        if (data == (unsigned char *) stackData)
        {
            if (amountToAllocate > BITSTREAM_STACK_ALLOCATION_SIZE)
            {
                data = (unsigned char *) malloc((size_t) amountToAllocate);
                RakAssert(data);  // TODO: introduce optional exceptions instead RakAssert

                // need to copy the stack data over to our new memory area too
                memcpy((void *) data, (void *) stackData, (size_t) BITS_TO_BYTES(numberOfBitsAllocated));

            }
        }
        else
        {
            auto tmp = (unsigned char *) realloc(data, (size_t) amountToAllocate);
            RakAssert(tmp); // Make sure realloc succeeded
            if (tmp != nullptr)
            {
                data = tmp;
            }
        }

        //  memset(data+newByteOffset, 0,  ((newNumberOfBitsAllocated-1)>>3) - ((numberOfBitsAllocated-1)>>3)); // Set the new data block to 0
    }

    if (newNumberOfBitsAllocated > numberOfBitsAllocated)
        numberOfBitsAllocated = newNumberOfBitsAllocated;
}

BitSize_t BitStream::GetNumberOfBitsAllocated() const
{
    return numberOfBitsAllocated;
}

void BitStream::PadWithZeroToByteLength(unsigned int bytes)
{
    if (GetNumberOfBytesUsed() < bytes)
    {
        AlignWriteToByteBoundary();
        unsigned int numToWrite = bytes - GetNumberOfBytesUsed();
        AddBitsAndReallocate(BYTES_TO_BITS(numToWrite));
        memset(data + BITS_TO_BYTES(numberOfBitsUsed), 0, (size_t) numToWrite);
        numberOfBitsUsed += BYTES_TO_BITS(numToWrite);
    }
}

/* 
// Julius Goryavsky's version of Harley's algorithm.
// 17 elementary ops plus an indexed load, if the machine
// has "and not."

int nlz10b(unsigned x) {

   static char table[64] =
     {32,20,19, u, u,18, u, 7,  10,17, u, u,14, u, 6, u,
       u, 9, u,16, u, u, 1,26,   u,13, u, u,24, 5, u, u,
       u,21, u, 8,11, u,15, u,   u, u, u, 2,27, 0,25, u,
      22, u,12, u, u, 3,28, u,  23, u, 4,29, u, u,30,31};

   x = x | (x >> 1);    // Propagate leftmost
   x = x | (x >> 2);    // 1-bit to the right.
   x = x | (x >> 4);
   x = x | (x >> 8);
   x = x & ~(x >> 16);
   x = x*0xFD7049FF;    // Activate this line or the following 3.
// x = (x << 9) - x;    // Multiply by 511.
// x = (x << 11) - x;   // Multiply by 2047.
// x = (x << 14) - x;   // Multiply by 16383.
   return table[x >> 26];
}
*/

// Should hit if reads didn't match writes
void BitStream::AssertStreamEmpty()
{
    RakAssert(readOffset == numberOfBitsUsed);
}

void BitStream::PrintBits(char *out) const
{
    if (numberOfBitsUsed <= 0)
    {
        strcpy(out, "No bits\n");
        return;
    }

    unsigned int strIndex = 0;
    for (BitSize_t counter = 0; counter < BITS_TO_BYTES(numberOfBitsUsed) && strIndex < 2000; counter++)
    {
        BitSize_t stop;

        if (counter == (numberOfBitsUsed - 1) >> 3)
            stop = 8 - (((numberOfBitsUsed - 1) & 7) + 1);
        else
            stop = 0;

        for (BitSize_t counter2 = 7; counter2 >= stop; counter2--)
        {
            if ((data[counter] >> counter2) & 1)
                out[strIndex++] = '1';
            else
                out[strIndex++] = '0';

            if (counter2 == 0)
                break;
        }

        out[strIndex++] = ' ';
    }

    out[strIndex++] = '\n';

    out[strIndex] = 0;
}

void BitStream::PrintBits() const
{
    char out[2048];
    PrintBits(out);
    CRABNET_DEBUG_PRINTF("%s", out);
}

void BitStream::PrintHex(char *out) const
{
    for (BitSize_t i = 0; i < GetNumberOfBytesUsed(); i++)
        sprintf(out + i * 3, "%02x ", data[i]);
}

void BitStream::PrintHex() const
{
    char out[2048];
    PrintHex(out);
    CRABNET_DEBUG_PRINTF("%s", out);
}

// Exposes the data for you to look at, like PrintBits does.
// Data will point to the stream.  Returns the length in bits of the stream.
BitSize_t BitStream::CopyData(unsigned char **_data) const
{
    RakAssert(numberOfBitsUsed > 0);

    *_data = (unsigned char *) malloc((size_t) BITS_TO_BYTES(numberOfBitsUsed));
    memcpy(*_data, data, sizeof(unsigned char) * (size_t) (BITS_TO_BYTES(numberOfBitsUsed)));
    return numberOfBitsUsed;
}

// Ignore data we don't intend to read
void BitStream::IgnoreBits(BitSize_t numberOfBits)
{
    readOffset += numberOfBits;
}

void BitStream::IgnoreBytes(unsigned int numberOfBytes)
{
    IgnoreBits(BYTES_TO_BITS(numberOfBytes));
}

// Move the write pointer to a position on the array.  Dangerous if you don't know what you are doing!
// Doesn't work with non-aligned data!
void BitStream::SetWriteOffset(BitSize_t offset)
{
    numberOfBitsUsed = offset;
}

/*
BitSize_t BitStream::GetWriteOffset( void ) const
{
return numberOfBitsUsed;
}

// Returns the length in bits of the stream
BitSize_t BitStream::GetNumberOfBitsUsed( void ) const
{
return GetWriteOffset();
}

// Returns the length in bytes of the stream
BitSize_t BitStream::GetNumberOfBytesUsed( void ) const
{
return BITS_TO_BYTES( numberOfBitsUsed );
}

// Returns the number of bits into the stream that we have read
BitSize_t BitStream::GetReadOffset( void ) const
{
return readOffset;
}


// Sets the read bit index
void BitStream::SetReadOffset( const BitSize_t newReadOffset )
{
readOffset=newReadOffset;
}

// Returns the number of bits left in the stream that haven't been read
BitSize_t BitStream::GetNumberOfUnreadBits( void ) const
{
return numberOfBitsUsed - readOffset;
}
// Exposes the internal data
unsigned char* BitStream::GetData( void ) const
{
return data;
}

*/
// If we used the constructor version with copy data off, this makes sure it is set to on and the data pointed to is copied.
void BitStream::AssertCopyData()
{
    if (!copyData)
    {
        copyData = true;

        if (numberOfBitsAllocated > 0)
        {
            auto newdata = (unsigned char *) malloc((size_t) BITS_TO_BYTES(numberOfBitsAllocated));

            RakAssert(newdata); // TODO: introduce optional exceptions instead RakAssert


            memcpy(newdata, data, (size_t) BITS_TO_BYTES(numberOfBitsAllocated));
            data = newdata;
        }

        else
            data = nullptr;
    }
}

bool BitStream::IsNetworkOrderInternal()
{
    static bool htonlValue = htonl(12345) == 12345UL;
    return htonlValue;

}

void BitStream::ReverseBytes(unsigned char *inByteArray, unsigned char *inOutByteArray, unsigned int length)
{
    for (BitSize_t i = 0; i < length; i++)
        inOutByteArray[i] = inByteArray[length - i - 1];
}

void BitStream::ReverseBytesInPlace(unsigned char *inOutData, unsigned int length)
{
    std::reverse(inOutData, inOutData + length);
}

bool BitStream::Read(char *varString)
{
    return RakString::Deserialize(varString, this);
}

bool BitStream::Read(unsigned char *varString)
{
    return RakString::Deserialize((char *) varString, this);
}

void BitStream::WriteAlignedVar8(const char *inByteArray)
{
    RakAssert((numberOfBitsUsed & 7) == 0);
    AddBitsAndReallocate(1 * 8);
    data[(numberOfBitsUsed >> 3) + 0] = (unsigned char) inByteArray[0];
    numberOfBitsUsed += 1 * 8;
}

bool BitStream::ReadAlignedVar8(char *inOutByteArray)
{
    RakAssert((readOffset & 7) == 0);
    if (readOffset + 1 * 8 > numberOfBitsUsed)
        return false;

    inOutByteArray[0] = data[(readOffset >> 3) + 0];
    readOffset += 1 * 8;
    return true;
}

void BitStream::WriteAlignedVar16(const char *inByteArray)
{
    RakAssert((numberOfBitsUsed & 7) == 0);
    AddBitsAndReallocate(2 * 8);
#ifndef __BITSTREAM_NATIVE_END
    if (DoEndianSwap())
    {
        data[(numberOfBitsUsed >> 3) + 0] = (unsigned char) inByteArray[1];
        data[(numberOfBitsUsed >> 3) + 1] = (unsigned char) inByteArray[0];
    }
    else
#endif
    {
        data[(numberOfBitsUsed >> 3) + 0] = (unsigned char) inByteArray[0];
        data[(numberOfBitsUsed >> 3) + 1] = (unsigned char) inByteArray[1];
    }

    numberOfBitsUsed += 2 * 8;
}

bool BitStream::ReadAlignedVar16(char *inOutByteArray)
{
    RakAssert((readOffset & 7) == 0);
    if (readOffset + 2 * 8 > numberOfBitsUsed)
        return false;
#ifndef __BITSTREAM_NATIVE_END
    if (DoEndianSwap())
    {
        inOutByteArray[0] = data[(readOffset >> 3) + 1];
        inOutByteArray[1] = data[(readOffset >> 3) + 0];
    }
    else
#endif
    {
        inOutByteArray[0] = data[(readOffset >> 3) + 0];
        inOutByteArray[1] = data[(readOffset >> 3) + 1];
    }

    readOffset += 2 * 8;
    return true;
}

void BitStream::WriteAlignedVar32(const char *inByteArray)
{
    RakAssert((numberOfBitsUsed & 7) == 0);
    AddBitsAndReallocate(4 * 8);
#ifndef __BITSTREAM_NATIVE_END
    if (DoEndianSwap())
    {
        data[(numberOfBitsUsed >> 3) + 0] = (unsigned char) inByteArray[3];
        data[(numberOfBitsUsed >> 3) + 1] = (unsigned char) inByteArray[2];
        data[(numberOfBitsUsed >> 3) + 2] = (unsigned char) inByteArray[1];
        data[(numberOfBitsUsed >> 3) + 3] = (unsigned char) inByteArray[0];
    }
    else
#endif
    {
        data[(numberOfBitsUsed >> 3) + 0] = (unsigned char) inByteArray[0];
        data[(numberOfBitsUsed >> 3) + 1] = (unsigned char) inByteArray[1];
        data[(numberOfBitsUsed >> 3) + 2] = (unsigned char) inByteArray[2];
        data[(numberOfBitsUsed >> 3) + 3] = (unsigned char) inByteArray[3];
    }

    numberOfBitsUsed += 4 * 8;
}

bool BitStream::ReadAlignedVar32(char *inOutByteArray)
{
    RakAssert((readOffset & 7) == 0);
    if (readOffset + 4 * 8 > numberOfBitsUsed)
        return false;
#ifndef __BITSTREAM_NATIVE_END
    if (DoEndianSwap())
    {
        inOutByteArray[0] = data[(readOffset >> 3) + 3];
        inOutByteArray[1] = data[(readOffset >> 3) + 2];
        inOutByteArray[2] = data[(readOffset >> 3) + 1];
        inOutByteArray[3] = data[(readOffset >> 3) + 0];
    }
    else
#endif
    {
        inOutByteArray[0] = data[(readOffset >> 3) + 0];
        inOutByteArray[1] = data[(readOffset >> 3) + 1];
        inOutByteArray[2] = data[(readOffset >> 3) + 2];
        inOutByteArray[3] = data[(readOffset >> 3) + 3];
    }

    readOffset += 4 * 8;
    return true;
}

bool BitStream::ReadFloat16(float &outFloat, float floatMin, float floatMax)
{
    unsigned short percentile;
    if (Read(percentile))
    {
        RakAssert(floatMax > floatMin);
        outFloat = floatMin + ((float) percentile / 65535.0f) * (floatMax - floatMin);
        if (outFloat < floatMin)
            outFloat = floatMin;
        else if (outFloat > floatMax)
            outFloat = floatMax;
        return true;
    }
    return false;
}

bool BitStream::SerializeFloat16(bool writeToBitstream, float &inOutFloat, float floatMin, float floatMax)
{
    if (writeToBitstream)
        WriteFloat16(inOutFloat, floatMin, floatMax);
    else
        return ReadFloat16(inOutFloat, floatMin, floatMax);
    return true;
}

void BitStream::WriteFloat16(float inOutFloat, float floatMin, float floatMax)
{
    RakAssert(floatMax > floatMin);
    if (inOutFloat > floatMax + .001)
        RakAssert(inOutFloat <= floatMax + .001);
    if (inOutFloat < floatMin - .001)
        RakAssert(inOutFloat >= floatMin - .001);
    float percentile = 65535.0f * (inOutFloat - floatMin) / (floatMax - floatMin);
    if (percentile < 0.0)
        percentile = 0.0;
    if (percentile > 65535.0f)
        percentile = 65535.0f;
    Write((unsigned short) percentile);
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif
