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

/**
* @file 
* @brief CheckSum implementation from http://www.flounder.com/checksum.htm
* 
*/
#include "CheckSum.h"

template<typename T>
union Type
{
    T value;
    unsigned char bytes[sizeof(T)];
};

/****************************************************************************
*        CheckSum::add
* Inputs:
*   unsigned int d: word to add
* Result: void
* 
* Effect: 
*   Adds the bytes of the unsigned int to the CheckSum
****************************************************************************/

void CheckSum::Add(unsigned int value)
{
    Type<unsigned int> data{};
    data.value = value;

    for (const unsigned char &byte : data.bytes)
        Add(byte);
} // CheckSum::add(unsigned int)

/****************************************************************************
*       CheckSum::add
* Inputs:
*   unsigned short value:
* Result: void
* 
* Effect: 
*   Adds the bytes of the unsigned short value to the CheckSum
****************************************************************************/

void CheckSum::Add(unsigned short value)
{
    Type<unsigned short> data{};
    data.value = value;

    for (const unsigned char &byte : data.bytes)
        Add(byte);
}

/****************************************************************************
*       CheckSum::add
* Inputs:
*   unsigned char value:
* Result: void
* 
* Effect: 
*   Adds the byte to the CheckSum
****************************************************************************/

void CheckSum::Add(unsigned char value)
{
    auto cipher = (unsigned char) (value ^ (r >> 8));
    r = (cipher + r) * c1 + c2;
    sum += cipher;
}


/****************************************************************************
*       CheckSum::add
* Inputs:
*   LPunsigned char b: pointer to byte array
*   unsigned int length: count
* Result: void
* 
* Effect: 
*   Adds the bytes to the CheckSum
****************************************************************************/

void CheckSum::Add(unsigned char *b, unsigned int length)
{
    for (unsigned int i = 0; i < length; i++)
        Add(b[i]);
}

CheckSum::CheckSum()
{
    Clear();
}

void CheckSum::Clear()
{
    sum = 0;
    r = 55665;
    c1 = 52845;
    c2 = 22719;
}

unsigned int CheckSum::Get()
{
    return 0;
}
