#ifndef OPENMW_PROCESSORACTORDEATH_HPP
#define OPENMW_PROCESSORACTORDEATH_HPP

#include "../ActorProcessor.hpp"
#include "apps/openmw/mwmp/Main.hpp"
#include "apps/openmw/mwmp/CellController.hpp"

namespace mwmp
{
    class ProcessorActorDeath final: public ActorProcessor
    {
    public:
        ProcessorActorDeath()
        {
            BPP_INIT(ID_ACTOR_DEATH);
        }

        virtual void Do(ActorPacket &packet, ActorList &actorList)
        {
            Main::get().getCellController()->readDeath(actorList);
        }
    };
}

#endif //OPENMW_PROCESSORACTORDEATH_HPP
