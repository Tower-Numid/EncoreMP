#ifndef OPENMW_PLAYERLIST_HPP
#define OPENMW_PLAYERLIST_HPP

#include <components/esm/custommarkerstate.hpp>
#include <components/esm/loadnpc.hpp>
#include <components/openmw-mp/Base/BasePlayer.hpp>

#include "../mwmechanics/aisequence.hpp"

#include "../mwworld/manualref.hpp"

#include "DedicatedPlayer.hpp"

#include <map>
#include <RakNetTypes.h>

namespace MWMechanics
{
    class Actor;
}

namespace mwmp
{
    class PlayerList
    {
    public:

        static void update(float dt);

        static DedicatedPlayer *newPlayer(RakNet::RakNetGUID guid);

        static void deletePlayer(RakNet::RakNetGUID guid);
        static void cleanUp();

        static DedicatedPlayer *getPlayer(RakNet::RakNetGUID guid);
        static DedicatedPlayer *getPlayer(const MWWorld::Ptr &ptr);
        static DedicatedPlayer* getPlayer(int actorId);
        static std::vector<RakNet::RakNetGUID> getPlayersInCell(const ESM::Cell& cell);

        static bool isDedicatedPlayer(const MWWorld::Ptr &ptr);

        static void enableMarkers(const ESM::Cell& cell);

        static void clearHitAttemptActorId(int actorId);

    private:

        static std::map<RakNet::RakNetGUID, DedicatedPlayer *> playerList;
    };
}

#endif //OPENMW_PLAYERLIST_HPP
