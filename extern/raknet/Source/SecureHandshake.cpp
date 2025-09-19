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


#include "NativeFeatureIncludes.h"

#ifdef LIBCAT_SECURITY
#include "SecureHandshake.h"

#include "cat/src/port/EndianNeutral.cpp"
#include "cat/src/port/AlignedAlloc.cpp"
#include "cat/src/time/Clock.cpp"
#include "cat/src/threads/Mutex.cpp"
#include "cat/src/threads/Thread.cpp"
#include "cat/src/threads/WaitableFlag.cpp"
#include "cat/src/hash/MurmurHash2.cpp"
#include "cat/src/lang/Strings.cpp"

#include "cat/src/math/BigRTL.cpp"
#include "cat/src/math/BigPseudoMersenne.cpp"
#include "cat/src/math/BigTwistedEdwards.cpp"

#include "cat/src/crypt/SecureCompare.cpp"
#include "cat/src/crypt/cookie/CookieJar.cpp"
#include "cat/src/crypt/hash/HMAC_MD5.cpp"
#include "cat/src/crypt/privatekey/ChaCha.cpp"
#include "cat/src/crypt/hash/Skein.cpp"
#include "cat/src/crypt/hash/Skein256.cpp"
#include "cat/src/crypt/hash/Skein512.cpp"
#include "cat/src/crypt/pass/Passwords.cpp"

#include "cat/src/crypt/rand/EntropyWindows.cpp"
#include "cat/src/crypt/rand/EntropyLinux.cpp"
#include "cat/src/crypt/rand/EntropyWindowsCE.cpp"
#include "cat/src/crypt/rand/EntropyGeneric.cpp"
#include "cat/src/crypt/rand/Fortuna.cpp"

#include "cat/src/crypt/tunnel/KeyAgreement.cpp"
#include "cat/src/crypt/tunnel/AuthenticatedEncryption.cpp"
#include "cat/src/crypt/tunnel/KeyAgreementInitiator.cpp"
#include "cat/src/crypt/tunnel/KeyAgreementResponder.cpp"
#include "cat/src/crypt/tunnel/KeyMaker.cpp"

#include "cat/src/crypt/tunnel/EasyHandshake.cpp"

#endif // LIBCAT_SECURITY
