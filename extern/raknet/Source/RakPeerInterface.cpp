#include "RakPeerInterface.h"
using namespace RakNet;

#if defined(_WIN32)

#include "GetTime.h"
#include "RakSleep.h"

uint64_t RakPeerInterface::Get64BitUniqueRandomNumber(void)
{
    uint64_t g=RakNet::GetTimeUS();

    RakNet::TimeUS lastTime, thisTime;
    int j;
    // Sleep a small random time, then use the last 4 bits as a source of randomness
    for (j=0; j < 8; j++)
    {
        lastTime = RakNet::GetTimeUS();
        RakSleep(1);
        RakSleep(0);
        thisTime = RakNet::GetTimeUS();
        RakNet::TimeUS diff = thisTime-lastTime;
        unsigned int diff4Bits = (unsigned int) (diff & 15);
        diff4Bits <<= 32-4;
        diff4Bits >>= j*4;
        ((char*)&g)[j] ^= diff4Bits;
    }
    return g;
}
#else
#include "gettimeofday.h"

uint64_t RakPeerInterface::Get64BitUniqueRandomNumber(void)
{
    // Mac address is a poor solution because you can't have multiple connections from the same system

    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec + tv.tv_sec * 1000000;
}
#endif
