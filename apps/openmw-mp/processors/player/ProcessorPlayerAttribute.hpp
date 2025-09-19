#ifndef OPENMW_PROCESSORPLAYERATTRIBUTE_HPP
#define OPENMW_PROCESSORPLAYERATTRIBUTE_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerAttribute : public PlayerProcessor
    {
    public:
        ProcessorPlayerAttribute()
        {
            BPP_INIT(ID_PLAYER_ATTRIBUTE)
        }

        void Do(PlayerPacket &packet, Player &player) override
        {
            if (!player.creatureStats.mDead)
            {
                //myPacket->Send(player, true);

                player.sendToLoaded(&packet);

                Script::Call<Script::CallbackIdentity("OnPlayerAttribute")>(player.getId());
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERATTRIBUTE_HPP
