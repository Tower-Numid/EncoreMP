#ifndef OPENMW_PROCESSOROBJECTSOUND_HPP
#define OPENMW_PROCESSOROBJECTSOUND_HPP

#include "BaseObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorObjectSound final: public BaseObjectProcessor
    {
    public:
        ProcessorObjectSound()
        {
            BPP_INIT(ID_OBJECT_SOUND)
        }

        virtual void Do(ObjectPacket &packet, ObjectList &objectList)
        {
            BaseObjectProcessor::Do(packet, objectList);

            ptrCellStore = Main::get().getCellController()->getCellStore(objectList.cell);

            if (!ptrCellStore) return;

            MWBase::World* world = MWBase::Environment::get().getWorld();

            // Only play sounds in active cells
            if (world->isCellActive(*ptrCellStore->getCell()))
            {
                objectList.playObjectSounds(ptrCellStore);
            }
        }

    };
}

#endif //OPENMW_PROCESSOROBJECTSOUND_HPP
