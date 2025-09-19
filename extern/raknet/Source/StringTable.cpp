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

#include "StringTable.h"
#include <string.h>
#include "RakAssert.h"
#include <stdio.h>
#include <cstdlib>
#include "BitStream.h"
#include "StringCompressor.h"

using namespace RakNet;

StringTable *StringTable::instance = 0;
int StringTable::referenceCount = 0;


int RakNet::StrAndBoolComp(char *const &key, const StrAndBool &data)
{
    return strcmp(key, (const char *) data.str);
}

StringTable::StringTable()
{

}

StringTable::~StringTable()
{
    for (unsigned i = 0; i < orderedStringList.Size(); i++)
    {
        if (orderedStringList[i].b)
            free(orderedStringList[i].str);
    }
}

StringTable &StringTable::Instance(void)
{
    static StringTable instance;
    return instance;
}

void StringTable::AddString(const char *str, bool copyString)
{
    StrAndBool sab;
    sab.b = copyString;
    if (copyString)
    {
        sab.str = (char *) malloc(strlen(str) + 1);
        RakAssert(sab.str);
        strcpy(sab.str, str);
    }
    else
        sab.str = (char *) str;

    // If it asserts inside here you are adding duplicate strings.
    orderedStringList.Insert(sab.str, sab, true);

    // If this assert hits you need to increase the range of StringTableType
    RakAssert(orderedStringList.Size() < (StringTableType) -1);
}

void StringTable::EncodeString(const char *input, size_t maxCharsToWrite, RakNet::BitStream *output)
{
    bool objectExists;
    // This is fast because the list is kept ordered.
    unsigned index = orderedStringList.GetIndexFromKey((char *) input, &objectExists);
    if (objectExists)
    {
        output->Write(true);
        output->Write((StringTableType) index);
    }
    else
    {
        LogStringNotFound(input);
        output->Write(false);
        StringCompressor::Instance().EncodeString(input, maxCharsToWrite, output);
    }
}

bool StringTable::DecodeString(char *output, size_t maxCharsToWrite, RakNet::BitStream *input)
{
    RakAssert(maxCharsToWrite > 0);

    if (maxCharsToWrite == 0)
        return false;
    bool hasIndex = false;
    if (!input->Read(hasIndex))
        return false;
    if (!hasIndex)
        StringCompressor::Instance().DecodeString(output, maxCharsToWrite, input);
    else
    {
        StringTableType index;
        if (!input->Read(index))
            return false;
        if (index >= orderedStringList.Size())
        {
            // Critical error - got a string index out of range, which means AddString was called more times on the remote system than on this system.
            // All systems must call AddString the same number of types, with the same strings in the same order.
            RakAssert(0);
            return false;
        }

        strncpy(output, orderedStringList[index].str, maxCharsToWrite);
        output[maxCharsToWrite - 1] = 0;
    }

    return true;
}

void StringTable::LogStringNotFound(const char *strName)
{
    (void) strName;

#ifdef _DEBUG
    CRABNET_DEBUG_PRINTF("Efficiency Warning! Unregistered String %s sent to StringTable.\n", strName);
#endif
}
