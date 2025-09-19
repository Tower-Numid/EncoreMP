#ifndef OPENMW_PROCESSORACTOREQUIPMENT_HPP
#define OPENMW_PROCESSORACTOREQUIPMENT_HPP

#include "../ActorProcessor.hpp"

namespace mwmp
{
    class ProcessorActorEquipment : public ActorProcessor
    {
    public:
        ProcessorActorEquipment()
        {
            BPP_INIT(ID_ACTOR_EQUIPMENT)
        }

        void Do(ActorPacket &packet, Player &player, BaseActorList &actorList) override
        {
            // Send only to players who have the cell loaded
            Cell *serverCell = CellController::get()->getCell(&actorList.cell);

            if (serverCell != nullptr)
            {
                Script::Call<Script::CallbackIdentity("OnActorEquipment")>(player.getId(), actorList.cell.getShortDescription().c_str());

                serverCell->sendToLoaded(&packet, &actorList);
            }
        }
    };
}

#endif //OPENMW_PROCESSORACTOREQUIPMENT_HPP
