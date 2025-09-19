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

#include "GetTime.h"

#include <chrono>

#if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT > 0
#include "SimpleMutex.h"
RakNet::TimeUS lastNormalizedReturnedValue=0;
RakNet::TimeUS lastNormalizedInputValue=0;
/// This constraints timer forward jumps to 1 second, and does not let it jump backwards
/// See http://support.microsoft.com/kb/274323 where the timer can sometimes jump forward by hours or days
/// This also has the effect where debugging a sending system won't treat the time spent halted past 1 second as elapsed network time
RakNet::TimeUS NormalizeTime(RakNet::TimeUS timeIn)
{
    RakNet::TimeUS diff, lastNormalizedReturnedValueCopy;
    static RakNet::SimpleMutex mutex;

    mutex.Lock();
    if (timeIn>=lastNormalizedInputValue)
    {
        diff = timeIn-lastNormalizedInputValue;
        if (diff > GET_TIME_SPIKE_LIMIT)
            lastNormalizedReturnedValue+=GET_TIME_SPIKE_LIMIT;
        else
            lastNormalizedReturnedValue+=diff;
    }
    else
        lastNormalizedReturnedValue+=GET_TIME_SPIKE_LIMIT;

    lastNormalizedInputValue=timeIn;
    lastNormalizedReturnedValueCopy=lastNormalizedReturnedValue;
    mutex.Unlock();

    return lastNormalizedReturnedValueCopy;
}
#endif // #if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT>0

RakNet::Time RakNet::GetTime()
{
    return (RakNet::Time) (GetTimeUS() / 1000);
}

RakNet::TimeMS RakNet::GetTimeMS()
{
    return (RakNet::TimeMS) (GetTimeUS() / 1000);
}

RakNet::TimeUS RakNet::GetTimeUS()
{
    using namespace std::chrono;
    static auto initialTime = steady_clock::now();

    auto curTime = duration_cast<duration<uint64_t, std::micro>>(steady_clock::now() - initialTime).count();
#if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT > 0
    return NormalizeTime(curTime);
#else
    return curTime;
#endif
}

constexpr RakNet::Time halfSpan = ((RakNet::Time) (const RakNet::Time) -1) / (RakNet::Time) 2;

bool RakNet::GreaterThan(RakNet::Time a, RakNet::Time b)
{
    // a > b?
    return b != a && b - a > halfSpan;
}

bool RakNet::LessThan(RakNet::Time a, RakNet::Time b)
{
    // a < b?
    return b != a && b - a < halfSpan;
}
