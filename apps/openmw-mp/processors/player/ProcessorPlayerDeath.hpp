#ifndef OPENMW_PROCESSORPLAYERDEATH_HPP
#define OPENMW_PROCESSORPLAYERDEATH_HPP

#include "../PlayerProcessor.hpp"
#include <chrono>

namespace mwmp
{
    class ProcessorPlayerDeath : public PlayerProcessor
    {
    public:
        ProcessorPlayerDeath()
        {
            BPP_INIT(ID_PLAYER_DEATH)
        }

        void Do(PlayerPacket &packet, Player &player) override
        {
            LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "Received %s from %s", strPacketID.c_str(), player.npc.mName.c_str());

            player.creatureStats.mDead = true;

            packet.Send(true);

            Script::Call<Script::CallbackIdentity("OnPlayerDeath")>(player.getId());
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERDEATH_HPP
