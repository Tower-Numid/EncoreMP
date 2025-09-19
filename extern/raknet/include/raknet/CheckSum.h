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

///
/// \file CheckSum.cpp
/// \brief [Internal] CheckSum implementation from http://www.flounder.com/checksum.htm
///

#ifndef __CHECKSUM_H
#define __CHECKSUM_H


/// Generates and validates checksums
class CheckSum
{
public:

    /// Default constructor

    CheckSum();

    void Clear();

    void Add(unsigned int w);


    void Add(unsigned short w);

    void Add(unsigned char *b, unsigned int length);

    void Add(unsigned char b);

    unsigned int Get();

protected:
    unsigned short r;
    unsigned short c1;
    unsigned short c2;
    unsigned int sum;
};

#endif
