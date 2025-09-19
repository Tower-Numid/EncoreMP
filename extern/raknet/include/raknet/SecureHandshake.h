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


#ifndef SECURE_HANDSHAKE_H
#define SECURE_HANDSHAKE_H

#include "NativeFeatureIncludes.h"

#ifdef LIBCAT_SECURITY

// If building a RakNet DLL, be sure to tweak the CAT_EXPORT macro meaning
#if defined(_CRABNET_DLL)
# define CAT_BUILD_DLL
#else
# define CAT_NEUTER_EXPORT
#endif

// Include DependentExtensions in your path to include this
#include <cat/AllTunnel.hpp>

#endif // LIBCAT_SECURITY

#endif // SECURE_HANDSHAKE_H
