#ifndef OPENMW_PROCESSORACTORANIMFLAGS_HPP
#define OPENMW_PROCESSORACTORANIMFLAGS_HPP


#include "../ActorProcessor.hpp"
#include "apps/openmw/mwmp/Main.hpp"
#include "apps/openmw/mwmp/CellController.hpp"

namespace mwmp
{
    class ProcessorActorAnimFlags final: public ActorProcessor
    {
    public:
        ProcessorActorAnimFlags()
        {
            BPP_INIT(ID_ACTOR_ANIM_FLAGS);
        }

        virtual void Do(ActorPacket &packet, ActorList &actorList)
        {
            Main::get().getCellController()->readAnimFlags(actorList);
        }
    };
}

#endif //OPENMW_PROCESSORACTORANIMFLAGS_HPP
