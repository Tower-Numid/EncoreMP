#ifndef OPENMW_PROCESSORWORLDTIME_HPP
#define OPENMW_PROCESSORWORLDTIME_HPP

#include <apps/openmw/mwbase/world.hpp>
#include <apps/openmw/mwbase/environment.hpp>

#include "../WorldstateProcessor.hpp"

namespace mwmp
{
    class ProcessorWorldTime final: public WorldstateProcessor
    {
    public:
        ProcessorWorldTime()
        {
            BPP_INIT(ID_WORLD_TIME)
        }

        virtual void Do(WorldstatePacket &packet, Worldstate &worldstate)
        {
            MWBase::World *world = MWBase::Environment::get().getWorld();

            if (worldstate.time.hour != -1)
                world->setGlobalFloat("gamehour", worldstate.time.hour);

            if (worldstate.time.day != -1)
                world->setGlobalInt("day", worldstate.time.day);

            if (worldstate.time.month != -1)
                world->setGlobalInt("month", worldstate.time.month);

            if (worldstate.time.year != -1)
                world->setGlobalInt("year", worldstate.time.year);

            if (worldstate.time.timeScale != -1)
                world->setGlobalFloat("timescale", worldstate.time.timeScale);

            if (worldstate.time.daysPassed != -1)
                world->setGlobalInt("dayspassed", worldstate.time.daysPassed);
        }
    };
}



#endif //OPENMW_PROCESSORWORLDTIME_HPP
