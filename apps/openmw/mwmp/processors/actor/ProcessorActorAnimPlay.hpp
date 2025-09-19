#ifndef OPENMW_PROCESSORACTORANIMPLAY_HPP
#define OPENMW_PROCESSORACTORANIMPLAY_HPP


#include "../ActorProcessor.hpp"
#include "apps/openmw/mwmp/Main.hpp"
#include "apps/openmw/mwmp/CellController.hpp"

namespace mwmp
{
    class ProcessorActorAnimPlay final: public ActorProcessor
    {
    public:
        ProcessorActorAnimPlay()
        {
            BPP_INIT(ID_ACTOR_ANIM_PLAY);
        }

        virtual void Do(ActorPacket &packet, ActorList &actorList)
        {
            Main::get().getCellController()->readAnimPlay(actorList);
        }
    };
}

#endif //OPENMW_PROCESSORACTORANIMPLAY_HPP
