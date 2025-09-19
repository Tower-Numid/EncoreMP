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

#include "RakNetDefines.h"

#if defined(_WIN32) && !(defined(__GNUC__)  || defined(__GCCXML__)) && defined(_CRABNET_DLL)
#define RAK_DLL_EXPORT __declspec(dllexport)
#else
#define RAK_DLL_EXPORT  
#endif

#define STATIC_FACTORY_DECLARATIONS(x) static x* GetInstance(void); \
static void DestroyInstance( x *i);

#define STATIC_FACTORY_DEFINITIONS(x,y) x* x::GetInstance(void) {return new y;} \
void x::DestroyInstance( x *i) {delete ( y* ) i;}
