#ifndef OPENMW_PROCESSORACTOREQUIPMENT_HPP
#define OPENMW_PROCESSORACTOREQUIPMENT_HPP

#include "../ActorProcessor.hpp"
#include "apps/openmw/mwmp/Main.hpp"
#include "apps/openmw/mwmp/CellController.hpp"

namespace mwmp
{
    class ProcessorActorEquipment final: public ActorProcessor
    {
    public:
        ProcessorActorEquipment()
        {
            BPP_INIT(ID_ACTOR_EQUIPMENT);
        }

        virtual void Do(ActorPacket &packet, ActorList &actorList)
        {
            Main::get().getCellController()->readEquipment(actorList);
        }
    };
}

#endif //OPENMW_PROCESSORACTOREQUIPMENT_HPP
