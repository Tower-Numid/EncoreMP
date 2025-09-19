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
/// \brief \b Reference counted object. Very simple class for quick and dirty uses.
///



#ifndef __REF_COUNTED_OBJ_H
#define __REF_COUNTED_OBJ_H


/// World's simplest class :)
class RefCountedObj
{
    public:
        RefCountedObj() {refCount=1;}
        virtual ~RefCountedObj() {}
        void AddRef(void) {refCount++;}
        void Deref(void) {if (--refCount==0) delete this;}
        int refCount;
};

#endif
