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

#include "DataCompressor.h"
#include "DS_HuffmanEncodingTree.h"
#include "RakAssert.h"
#include <string.h> // Use string.h rather than memory.h for a console
#include <cstdlib>

using namespace RakNet;

STATIC_FACTORY_DEFINITIONS(DataCompressor,DataCompressor)

void DataCompressor::Compress( unsigned char *userData, unsigned sizeInBytes, RakNet::BitStream * output )
{
    // Don't use this for small files as you will just make them bigger!
    RakAssert(sizeInBytes > 2048);

    unsigned int frequencyTable[256];
    memset(frequencyTable, 0, 256 * sizeof(unsigned int));
    for (unsigned i = 0; i < sizeInBytes; i++)
        ++frequencyTable[userData[i]];
    HuffmanEncodingTree tree;
    BitSize_t writeOffset1, writeOffset2, bitsUsed1, bitsUsed2;
    tree.GenerateFromFrequencyTable(frequencyTable);
    output->WriteCompressed(sizeInBytes);
    for (unsigned i = 0; i < 256; i++)
        output->WriteCompressed(frequencyTable[i]);
    output->AlignWriteToByteBoundary();
    writeOffset1 = output->GetWriteOffset();
    output->Write((unsigned int) 0);    // Dummy value
    bitsUsed1 = output->GetNumberOfBitsUsed();
    tree.EncodeArray(userData, sizeInBytes, output);
    bitsUsed2 = output->GetNumberOfBitsUsed();
    writeOffset2 = output->GetWriteOffset();
    output->SetWriteOffset(writeOffset1);
    output->Write(bitsUsed2 - bitsUsed1); // Go back and write how many bits were used for the encoding
    output->SetWriteOffset(writeOffset2);
}

unsigned DataCompressor::DecompressAndAllocate( RakNet::BitStream * input, unsigned char **output )
{
    HuffmanEncodingTree tree;
    unsigned int bitsUsed, destinationSizeInBytes;
    unsigned int decompressedBytes;
    unsigned int frequencyTable[256];

    input->ReadCompressed(destinationSizeInBytes);

    for (unsigned int &frequency : frequencyTable)
        input->ReadCompressed(frequency);

    input->AlignReadToByteBoundary();

    if (!input->Read(bitsUsed))
    {
        // Read error
#ifdef _DEBUG
        RakAssert(0);
#endif
        return 0;
    }
    *output = (unsigned char *) malloc(destinationSizeInBytes);
    tree.GenerateFromFrequencyTable(frequencyTable);
    decompressedBytes = tree.DecodeArray(input, bitsUsed, destinationSizeInBytes, *output);
    RakAssert(decompressedBytes == destinationSizeInBytes);
    return destinationSizeInBytes;
}
