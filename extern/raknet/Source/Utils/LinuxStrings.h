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

#ifndef _GCC_WIN_STRINGS
#define _GCC_WIN_STRINGS

#if ((defined(__GNUC__)  || defined(__GCCXML__) || defined(__S3E__) ) && !defined(_WIN32)) || defined(__native_client__)
        #ifndef _stricmp
            #include <cstring>
            #define _stricmp strcasecmp
        #endif
        #define _strnicmp strncasecmp
        #define _vsnprintf vsnprintf
        #if !defined(__APPLE__)
            char *_strlwr(char * str); //this won't compile on OSX for some reason
        #endif
#endif

#endif // _GCC_WIN_STRINGS
