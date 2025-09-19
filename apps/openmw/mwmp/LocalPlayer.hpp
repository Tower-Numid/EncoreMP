#ifndef OPENMW_LOCALPLAYER_HPP
#define OPENMW_LOCALPLAYER_HPP

#include <components/openmw-mp/Base/BasePlayer.hpp>
#include "../mwmechanics/activespells.hpp"
#include "../mwworld/ptr.hpp"
#include "../mwworld/timestamp.hpp"
#include <RakNetTypes.h>

namespace mwmp
{
    class Networking;
    class LocalPlayer : public BasePlayer
    {
    public:

        LocalPlayer();
        virtual ~LocalPlayer();

        time_t deathTime;
        bool receivedCharacter;

        bool isUsingBed;
        bool avoidSendingInventoryPackets;
        bool isReceivingQuickKeys;
        bool isPlayingAnimation;
        bool diedSinceArrestAttempt;
        unsigned int lastEnchantmentQuantity;

        void update();

        bool processCharGen();
        bool isLoggedIn();

        void updateStatsDynamic(bool forceUpdate = false);
        void updateAttributes(bool forceUpdate = false);
        void updateSkills(bool forceUpdate = false);
        void updateLevel(bool forceUpdate = false);
        void updateBounty(bool forceUpdate = false);
        void updateReputation(bool forceUpdate = false);
        void updatePosition(bool forceUpdate = false);
        void updateCell(bool forceUpdate = false);
        void updateEquipment(bool forceUpdate = false);
        void updateInventory(bool forceUpdate = false);
        void updateAttackOrCast();
        void updateAnimFlags(bool forceUpdate = false);

        void addItems();
        void addSpells();
        void addSpellsActive();
        void addJournalItems();
        void addTopics();

        void removeItems();
        void removeSpells();
        void removeSpellsActive();

        void die();
        void resurrect();

        void closeInventoryWindows();
        void updateInventoryWindow();

        void setCharacter();
        void setDynamicStats();
        void setAttributes();
        void setSkills();
        void setLevel();
        void setBounty();
        void setReputation();
        void setPosition();
        void setMomentum();
        void setCell();
        void setClass();
        void setEquipment();
        void setInventory();
        void setSpellbook();
        void setSpellsActive();
        void setCooldowns();
        void setQuickKeys();
        void setFactions();
        void setBooks();
        void setShapeshift();
        void setMarkLocation();
        void setSelectedSpell();

        void sendDeath(char newDeathState);
        void sendClass();
        void sendInventory();
        void sendItemChange(const mwmp::Item& item, unsigned int action);
        void sendItemChange(const MWWorld::Ptr& itemPtr, int count, unsigned int action);
        void sendItemChange(const std::string& refId, int count, unsigned int action);
        void sendStoredItemRemovals();
        void sendSpellbook();
        void sendSpellChange(std::string id, unsigned int action);
        void sendSpellsActive();
        void sendSpellsActiveAddition(const std::string id, bool isStackingSpell, const MWMechanics::ActiveSpells::ActiveSpellParams& params);
        void sendSpellsActiveRemoval(const std::string id, bool isStackingSpell, MWWorld::TimeStamp timestamp);
        void sendCooldownChange(std::string id, int startTimestampDay, float startTimestampHour);
        void sendQuickKey(unsigned short slot, int type, const std::string& itemId = "");
        void sendJournalEntry(const std::string& quest, int index, const MWWorld::Ptr& actor);
        void sendJournalIndex(const std::string& quest, int index);
        void sendFactionRank(const std::string& factionId, int rank);
        void sendFactionExpulsionState(const std::string& factionId, bool isExpelled);
        void sendFactionReputation(const std::string& factionId, int reputation);
        void sendTopic(const std::string& topic);
        void sendBook(const std::string& bookId);
        void sendWerewolfState(bool isWerewolf);
        void sendMarkLocation(const ESM::Cell& newMarkCell, const ESM::Position& newMarkPosition);
        void sendSelectedSpell(const std::string& newSelectedSpellId);
        void sendItemUse(const MWWorld::Ptr& itemPtr, bool usingItemMagic = false, char currentDrawState = 0);
        void sendCellStates();

        void clearCellStates();
        void clearCurrentContainer();

        void storeCellState(const ESM::Cell& cell, int stateType);
        void storeCurrentContainer(const MWWorld::Ptr& container);
        void storeItemRemoval(const std::string& refId, int count);
        void storeLastEnchantmentQuantity(unsigned int quantity);

        void playAnimation();
        void playSpeech();

        MWWorld::Ptr getPlayerPtr();

    private:
        Networking *getNetworking();

    };
}

#endif //OPENMW_LOCALPLAYER_HPP
