#ifndef OPENMW_PROCESSORPLAYERBOOK_HPP
#define OPENMW_PROCESSORPLAYERBOOK_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerBook final: public PlayerProcessor
    {
    public:
        ProcessorPlayerBook()
        {
            BPP_INIT(ID_PLAYER_BOOK)
        }

        virtual void Do(PlayerPacket &packet, BasePlayer *player)
        {
            if (isLocal())
            {
                static_cast<LocalPlayer*>(player)->setBooks();
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERBOOK_HPP
