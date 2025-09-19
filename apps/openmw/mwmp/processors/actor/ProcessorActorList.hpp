#ifndef OPENMW_PROCESSORACTORLIST_HPP
#define OPENMW_PROCESSORACTORLIST_HPP

#include "../ActorProcessor.hpp"
#include "apps/openmw/mwmp/Main.hpp"
#include "apps/openmw/mwmp/CellController.hpp"
#include "apps/openmw/mwmp/MechanicsHelper.hpp"

namespace mwmp
{
    class ProcessorActorList final: public ActorProcessor
    {
    public:
        ProcessorActorList()
        {
            BPP_INIT(ID_ACTOR_LIST)
        }

        virtual void Do(ActorPacket &packet, ActorList &actorList)
        {
            MWWorld::CellStore *ptrCellStore = Main::get().getCellController()->getCellStore(actorList.cell);

            if (!ptrCellStore) return;

            LOG_MESSAGE_SIMPLE(TimedLog::LOG_VERBOSE, "Received %s about %s", strPacketID.c_str(), actorList.cell.getShortDescription().c_str());
            LOG_APPEND(TimedLog::LOG_VERBOSE, "- action: %i", actorList.action);

            // If we've received a request for information, comply with it
            if (actorList.action == mwmp::BaseActorList::REQUEST)
            {
                MechanicsHelper::spawnLeveledCreatures(ptrCellStore);
                actorList.sendActorsInCell(ptrCellStore);
            }
        }
    };
}

#endif //OPENMW_PROCESSORACTORLIST_HPP
