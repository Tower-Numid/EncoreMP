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



#include "StringCompressor.h"
#include "DS_HuffmanEncodingTree.h"
#include "RakAlloca.h"
#include "BitStream.h"
#include "RakString.h"
#include "RakAssert.h"
#include <string.h>

#include <memory.h>

using namespace RakNet;

StringCompressor &StringCompressor::Instance()
{
    static StringCompressor instance;
    return instance;
}

unsigned int englishCharacterFrequencies[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 722, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11084, 58, 63,
        1, 0, 31, 0, 317, 64, 64, 44, 0, 695, 62, 980, 266, 69, 67, 56, 7, 73, 3, 14, 2, 69, 1, 167, 9, 1, 2, 25, 94, 0,
        195, 139, 34, 96, 48, 103, 56, 125, 653, 21, 5, 23, 64, 85, 44, 34, 7, 92, 76, 147, 12, 14, 57, 15, 39, 15, 1,
        1, 1, 2, 3, 0, 3611, 845, 1077, 1884, 5870, 841, 1057, 2501, 3212, 164, 531, 2019, 1330, 3056, 4037, 848, 47,
        2586, 2919, 4771, 1707, 535, 1106, 152, 1243, 100, 0, 2, 0, 10
};

StringCompressor::StringCompressor()
{
    DataStructures::Map<int, HuffmanEncodingTree *>::IMPLEMENT_DEFAULT_COMPARISON();

    // Make a default tree immediately, since this is used for RPC possibly from multiple threads at the same time
    auto huffmanEncodingTree = new HuffmanEncodingTree;
    huffmanEncodingTree->GenerateFromFrequencyTable(englishCharacterFrequencies);

    huffmanEncodingTrees.Set(0, huffmanEncodingTree);
}

void StringCompressor::GenerateTreeFromStrings(unsigned char *input, unsigned inputLength, uint8_t languageId)
{
    HuffmanEncodingTree *huffmanEncodingTree;
    if (huffmanEncodingTrees.Has(languageId))
    {
        huffmanEncodingTree = huffmanEncodingTrees.Get(languageId);
        delete huffmanEncodingTree;
    }

    if (inputLength == 0)
        return;

    unsigned int frequencyTable[256];

    // Generate the frequency table from the strings
    for (unsigned index = 0; index < inputLength; index++)
        frequencyTable[input[index]]++;

    // Build the tree
    huffmanEncodingTree = new HuffmanEncodingTree;
    huffmanEncodingTree->GenerateFromFrequencyTable(frequencyTable);
    huffmanEncodingTrees.Set(languageId, huffmanEncodingTree);
}

StringCompressor::~StringCompressor()
{
    for (unsigned i = 0; i < huffmanEncodingTrees.Size(); i++)
        delete huffmanEncodingTrees[i];
}

void StringCompressor::EncodeString(const char *input, size_t maxCharsToWrite, RakNet::BitStream *output, uint8_t languageId)
{
    if (!huffmanEncodingTrees.Has(languageId))
        return;

    auto huffmanEncodingTree = huffmanEncodingTrees.Get(languageId);

    if (input == nullptr)
    {
        output->WriteCompressed((uint32_t) 0);
        return;
    }

    size_t charsToWrite = strlen(input);

    if (maxCharsToWrite > 0 && charsToWrite > maxCharsToWrite)
        charsToWrite = maxCharsToWrite - 1;

    RakNet::BitStream encodedBitStream;
    huffmanEncodingTree->EncodeArray((unsigned char *) input, charsToWrite, &encodedBitStream);

    uint32_t stringBitLength = encodedBitStream.GetNumberOfBitsUsed();
    output->WriteCompressed(stringBitLength);
    output->WriteBits(encodedBitStream.GetData(), stringBitLength);
}

bool StringCompressor::DecodeString(char *output, size_t maxCharsToWrite, RakNet::BitStream *input, uint8_t languageId)
{
    if (!huffmanEncodingTrees.Has(languageId))
        return false;
    if (maxCharsToWrite <= 0)
        return false;

    HuffmanEncodingTree *huffmanEncodingTree = huffmanEncodingTrees.Get(languageId);

    output[0] = 0;

    uint32_t stringBitLength;
    if (!input->ReadCompressed(stringBitLength))
        return false;
    if (input->GetNumberOfUnreadBits() < stringBitLength)
        return false;

    size_t bytesInStream = huffmanEncodingTree->DecodeArray(input, stringBitLength, maxCharsToWrite, (unsigned char *) output);

    if (bytesInStream < maxCharsToWrite)
        output[bytesInStream] = 0;
    else
        output[maxCharsToWrite - 1] = 0;

    return true;
}

#ifdef _CSTRING_COMPRESSOR
void StringCompressor::EncodeString(const CString &input, int maxCharsToWrite, RakNet::BitStream *output)
{
    LPTSTR p = input;
    EncodeString(p, maxCharsToWrite*sizeof(TCHAR), output, languageID);
}
bool StringCompressor::DecodeString(CString &output, int maxCharsToWrite, RakNet::BitStream *input, uint8_t languageId)
{
    LPSTR p = output.GetBuffer(maxCharsToWrite*sizeof(TCHAR));
    DecodeString(p,maxCharsToWrite*sizeof(TCHAR), input, languageID);
    output.ReleaseBuffer(0)

}
#endif
#ifdef _STD_STRING_COMPRESSOR
void StringCompressor::EncodeString(const std::string &input, int maxCharsToWrite, RakNet::BitStream *output, uint8_t languageId)
{
    EncodeString(input.c_str(), maxCharsToWrite, output, languageId);
}
bool StringCompressor::DecodeString(std::string *output, int maxCharsToWrite, RakNet::BitStream *input, uint8_t languageId)
{
    if (maxCharsToWrite <= 0)
    {
        output->clear();
        return true;
    }

    bool out;

#if USE_ALLOCA==1
    if (maxCharsToWrite < MAX_ALLOCA_STACK_ALLOCATION)
    {
        char *destinationBlock = (char*) alloca(maxCharsToWrite);
        out=DecodeString(destinationBlock, maxCharsToWrite, input, languageId);
        *output=destinationBlock;
    }
    else
#endif
    {
        char *destinationBlock = (char*) malloc(maxCharsToWrite);
        out=DecodeString(destinationBlock, maxCharsToWrite, input, languageId);
        *output=destinationBlock;
        free(destinationBlock);
    }

    return out;
}
#endif

void StringCompressor::EncodeString(const RakString *input, size_t maxCharsToWrite, RakNet::BitStream *output, uint8_t languageId)
{
    EncodeString(input->C_String(), maxCharsToWrite, output, languageId);
}

bool StringCompressor::DecodeString(RakString *output, size_t maxCharsToWrite, RakNet::BitStream *input, uint8_t languageId)
{
    if (maxCharsToWrite <= 0)
    {
        output->Clear();
        return true;
    }

    bool out;

#if USE_ALLOCA == 1
    if (maxCharsToWrite < MAX_ALLOCA_STACK_ALLOCATION)
    {
        auto destinationBlock = (char *) alloca(maxCharsToWrite);
        out = DecodeString(destinationBlock, maxCharsToWrite, input, languageId);
        *output = destinationBlock;
    }
    else
#endif
    {
        auto destinationBlock = (char *) malloc(maxCharsToWrite);
        out = DecodeString(destinationBlock, maxCharsToWrite, input, languageId);
        *output = destinationBlock;
        free(destinationBlock);
    }

    return out;
}
