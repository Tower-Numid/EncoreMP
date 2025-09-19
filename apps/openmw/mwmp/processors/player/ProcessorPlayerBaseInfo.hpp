#ifndef OPENMW_PROCESSORPLAYERBASEINFO_HPP
#define OPENMW_PROCESSORPLAYERBASEINFO_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerBaseInfo final: public PlayerProcessor
    {
    public:
        ProcessorPlayerBaseInfo()
        {
            BPP_INIT(ID_PLAYER_BASEINFO)
        }

        virtual void Do(PlayerPacket &packet, BasePlayer *player)
        {
            LOG_MESSAGE_SIMPLE(TimedLog::LOG_INFO, "Received ID_PLAYER_BASEINFO from server");

            if (isLocal())
            {
                LOG_APPEND(TimedLog::LOG_INFO, "- Packet was about LocalPlayer");

                if (isRequest())
                {
                    LOG_APPEND(TimedLog::LOG_INFO, "- Requesting info");
                    packet.Send(serverAddr);
                }
                else
                {
                    LOG_APPEND(TimedLog::LOG_INFO, "- Setting character for LocalPlayer");
                    static_cast<LocalPlayer*>(player)->setCharacter();
                }
            }
            else
            {
                LOG_APPEND(TimedLog::LOG_INFO, "- Packet was about %s", player == 0 ? "new player" : player->npc.mName.c_str());

                if (player == 0)
                {
                    LOG_APPEND(TimedLog::LOG_INFO, "- Exchanging data with new player");
                    player = PlayerList::newPlayer(guid);

                    packet.setPlayer(player);
                    packet.Read();
                }

                static_cast<DedicatedPlayer*>(player)->setBaseInfo();
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERBASEINFO_HPP
