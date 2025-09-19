#ifndef OPENMW_DEDICATEDPLAYER_HPP
#define OPENMW_DEDICATEDPLAYER_HPP

#include <components/esm/custommarkerstate.hpp>
#include <components/esm/loadcrea.hpp>
#include <components/esm/loadnpc.hpp>
#include <components/openmw-mp/Base/BasePlayer.hpp>

#include "../mwclass/npc.hpp"

#include "../mwmechanics/aisequence.hpp"

#include "../mwworld/manualref.hpp"

#include <map>
#include <RakNetTypes.h>

namespace MWMechanics
{
    class Actor;
}

namespace mwmp
{
    class DedicatedPlayer : public BasePlayer
    {
        friend class PlayerList;

    public:

        void update(float dt);

        void move(float dt);
        void setBaseInfo();
        void setStatsDynamic();
        void setAnimFlags();
        void setAttributes();
        void setSkills();
        void setEquipment();
        void setShapeshift();
        void setCell();

        void playAnimation();
        void playSpeech();

        void equipItem(std::string itemId, bool noSound = false);
        void die();
        void resurrect();

        void addSpellsActive();
        void removeSpellsActive();
        void setSpellsActive();

        void updateMarker();
        void removeMarker();
        void enableMarker();

        void createReference(const std::string& recId);
        void deleteReference();

        MWWorld::Ptr getPtr();
        MWWorld::ManualRef* getRef();

        void setPtr(const MWWorld::Ptr& newPtr);
        void reloadPtr();

    private:

        DedicatedPlayer(RakNet::RakNetGUID guid);
        virtual ~DedicatedPlayer();

        MWWorld::ManualRef* reference;

        MWWorld::Ptr ptr;

        ESM::CustomMarker marker;
        bool markerEnabled;

        std::string previousRace;
        std::string previousCreatureRefId;
        bool previousDisplayCreatureName;

        std::string creatureRecordId;

        bool hasReceivedInitialEquipment;
        bool hasFinishedInitialTeleportation;
        bool isLevitationPurged;

        bool wasJumping;
    };
}
#endif //OPENMW_DEDICATEDPLAYER_HPP
