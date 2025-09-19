#ifndef OPENMW_PROCESSORACTORTEST_HPP
#define OPENMW_PROCESSORACTORTEST_HPP

#include "../ActorProcessor.hpp"

namespace mwmp
{
    class ProcessorActorTest : public ActorProcessor
    {
    public:
        ProcessorActorTest()
        {
            BPP_INIT(ID_ACTOR_TEST)
        }

        void Do(ActorPacket &packet, Player &player, BaseActorList &actorList) override
        {
            // Send only to players who have the cell loaded
            Cell *serverCell = CellController::get()->getCell(&actorList.cell);

            if (serverCell != nullptr)
                serverCell->sendToLoaded(&packet, &actorList);

            Script::Call<Script::CallbackIdentity("OnActorTest")>(player.getId(), actorList.cell.getShortDescription().c_str());
        }
    };
}

#endif //OPENMW_PROCESSORACTORTEST_HPP
