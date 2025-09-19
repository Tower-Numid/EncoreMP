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
/// \brief \b [Internal] Random number generator
///



#ifndef __RAND_H
#define __RAND_H 

#include "Export.h"

/// Initialise seed for Random Generator
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
/// \param[in] seed The seed value for the random number generator.
extern void RAK_DLL_EXPORT seedMT(unsigned int seed);

/// \internal
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
extern unsigned int RAK_DLL_EXPORT reloadMT();

/// Gets a random unsigned int
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
/// \return an integer random value.
extern unsigned int RAK_DLL_EXPORT randomMT();

/// Gets a random float
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
/// \return 0 to 1.0f, inclusive
extern float RAK_DLL_EXPORT frandomMT();

/// Randomizes a buffer
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
extern void RAK_DLL_EXPORT fillBufferMT( void *buffer, unsigned int bytes );

namespace RakNet {

// Same thing as above functions, but not global
class RAK_DLL_EXPORT RakNetRandom
{
public:
    RakNetRandom();
    ~RakNetRandom() = default;
    void SeedMT(unsigned int seed);
    unsigned int ReloadMT();
    unsigned int RandomMT();
    float FrandomMT();
    void FillBufferMT(void *buffer, unsigned int bytes);

protected:
    unsigned int state[624 + 1];
    unsigned int *next;
    int left;
};

} // namespace RakNet

#endif
