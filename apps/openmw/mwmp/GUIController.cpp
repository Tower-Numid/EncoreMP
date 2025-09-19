#include <components/openmw-mp/TimedLog.hpp>
#include <components/openmw-mp/Base/BasePlayer.hpp>

#include <SDL_system.h>

#include <MyGUI_FactoryManager.h>
#include <MyGUI_Gui.h>
#include <MyGUI_ImageBox.h>
#include <MyGUI_InputManager.h>
#include <MyGUI_LanguageManager.h>
#include <MyGUI_RenderManager.h>
#include <MyGUI_RotatingSkin.h>
#include <MyGUI_ScrollView.h>
#include <MyGUI_TextIterator.h>

#include <extern/PicoSHA2/picosha2.h>

#include "../mwbase/environment.hpp"
#include "../mwbase/windowmanager.hpp"
#include "../mwbase/inputmanager.hpp"

#include "../mwgui/mapwindow.hpp"

#include "../mwworld/worldimp.hpp"
#include "../mwworld/player.hpp"
#include "../mwworld/cellstore.hpp"

#include "GUIController.hpp"
#include "Main.hpp"
#include "Networking.hpp"
#include "GUI/PlayerMarkerCollection.hpp"
#include "GUI/GUIDialogList.hpp"
#include "GUI/GUIChat.hpp"
#include "LocalPlayer.hpp"
#include "DedicatedPlayer.hpp"
#include "PlayerList.hpp"


mwmp::GUIController::GUIController(): mInputBox(0), mListBox(0)
{
    mChat = nullptr;
    keySay = SDL_SCANCODE_Y;
    keyChatMode = SDL_SCANCODE_F2;
}

mwmp::GUIController::~GUIController()
{

}

void mwmp::GUIController::cleanUp()
{
    mPlayerMarkers.clear();
    if (mChat != nullptr)
        delete mChat;
    mChat = nullptr;
}

void mwmp::GUIController::refreshGuiMode(MWGui::GuiMode guiMode)
{
    if (MWBase::Environment::get().getWindowManager()->containsMode(guiMode))
    {
        MWBase::Environment::get().getWindowManager()->removeGuiMode(guiMode);
        MWBase::Environment::get().getWindowManager()->pushGuiMode(guiMode);
    }
}

void mwmp::GUIController::setupChat()
{
    assert(mChat == nullptr);

    float chatDelay = Settings::Manager::getFloat("delay", "Chat");
    int chatY = Settings::Manager::getInt("y", "Chat");
    int chatX = Settings::Manager::getInt("x", "Chat");
    int chatW = Settings::Manager::getInt("w", "Chat");
    int chatH = Settings::Manager::getInt("h", "Chat");

    keySay = SDL_GetScancodeFromName(Settings::Manager::getString("keySay", "Chat").c_str());
    keyChatMode = SDL_GetScancodeFromName(Settings::Manager::getString("keyChatMode", "Chat").c_str());

    mChat = new GUIChat(chatX, chatY, chatW, chatH);
    mChat->setDelay(chatDelay);
}

void mwmp::GUIController::printChatMessage(std::string &msg)
{
    if (mChat != nullptr)
        mChat->print(msg);
}


void mwmp::GUIController::setChatVisible(bool chatVisible)
{
    mChat->setVisible(chatVisible);
}

void mwmp::GUIController::showDialogList(const mwmp::BasePlayer::GUIMessageBox &guiMessageBox)
{
    MWBase::WindowManager *windowManager = MWBase::Environment::get().getWindowManager();
    
    if (mListBox != NULL)
    {
        windowManager->removeDialog(mListBox);
        windowManager->removeCurrentModal(mListBox);
        mListBox = NULL;
    }

    std::vector<std::string> list;

    std::string buf;

    for (const auto &data : guiMessageBox.data)
    {
        if (data == '\n')
        {
            list.push_back(buf);
            buf.erase();
            continue;
        }
        buf += data;
    }

    list.push_back(buf);

    mListBox = new GUIDialogList(guiMessageBox.label, list);
    windowManager->pushGuiMode((MWGui::GuiMode)GM_TES3MP_ListBox);
}

void mwmp::GUIController::showMessageBox(const BasePlayer::GUIMessageBox &guiMessageBox)
{
    MWBase::WindowManager *windowManager = MWBase::Environment::get().getWindowManager();
    windowManager->messageBox(guiMessageBox.label);
}

std::vector<std::string> splitString(const std::string &str, char delim = ';')
{
    std::istringstream ss(str);
    std::vector<std::string> result;
    std::string token;
    while (std::getline(ss, token, delim))
        result.push_back(token);
    return result;
}

void mwmp::GUIController::showCustomMessageBox(const BasePlayer::GUIMessageBox &guiMessageBox)
{
    MWBase::WindowManager* windowManager = MWBase::Environment::get().getWindowManager();
    std::vector<std::string> buttons = splitString(guiMessageBox.buttons);
    windowManager->interactiveMessageBox(guiMessageBox.label, buttons, false, true);
}

void mwmp::GUIController::showInputBox(const BasePlayer::GUIMessageBox &guiMessageBox)
{
    MWBase::WindowManager *windowManager = MWBase::Environment::get().getWindowManager();

    windowManager->removeDialog(mInputBox);
    windowManager->pushGuiMode((MWGui::GuiMode)GM_TES3MP_InputBox);
    mInputBox = 0;
    mInputBox = new TextInputDialog();

    mInputBox->setEditPassword(guiMessageBox.type == BasePlayer::GUIMessageBox::PasswordDialog);

    mInputBox->setTextLabel(guiMessageBox.label);
    mInputBox->setTextNote(guiMessageBox.note);

    mInputBox->eventDone += MyGUI::newDelegate(this, &GUIController::onInputBoxDone);

    mInputBox->setVisible(true);
}

void mwmp::GUIController::onInputBoxDone(MWGui::WindowBase *parWindow)
{
    LocalPlayer *localPlayer = Main::get().getLocalPlayer();
    std::string textInput = mInputBox->getTextInput();

    // Send input for password dialogs after it's been hashed and rehashed, for some slight
    // extra security that doesn't require the client to keep storing a salt
    if (localPlayer->guiMessageBox.type == BasePlayer::GUIMessageBox::PasswordDialog)
    {
        textInput = picosha2::hash256_hex_string(textInput);
        textInput = picosha2::hash256_hex_string(textInput + picosha2::hash256_hex_string(picosha2::hash256_hex_string((textInput))));
    }

    localPlayer->guiMessageBox.data = textInput;

    PlayerPacket *playerPacket = Main::get().getNetworking()->getPlayerPacket(ID_GUI_MESSAGEBOX);
    playerPacket->setPlayer(Main::get().getLocalPlayer());
    playerPacket->Send();

    MWBase::WindowManager *windowManager = MWBase::Environment::get().getWindowManager();
    windowManager->removeDialog(mInputBox);
    mInputBox = 0;
    windowManager->popGuiMode();
}

bool mwmp::GUIController::pressedKey(int key)
{
    MWBase::WindowManager *windowManager = MWBase::Environment::get().getWindowManager();
    if (mChat == nullptr || windowManager->isConsoleMode() || windowManager->getMode() != MWGui::GM_None)
        return false;
    if (key == keyChatMode)
    {
        mChat->pressedChatMode();
        return true;
    }
    else if (key == keySay)
    {
        mChat->pressedSay();
        return true;
    }
    return false;
}

void mwmp::GUIController::changeChatMode()
{
    mChat->pressedChatMode();
}

bool mwmp::GUIController::getChatEditState()
{
    return mChat->editState;
}

void mwmp::GUIController::update(float dt)
{
    if (mChat != nullptr)
        mChat->update(dt);
}

void mwmp::GUIController::processCustomMessageBoxInput(int pressedButton)
{
    LOG_MESSAGE_SIMPLE(TimedLog::LOG_VERBOSE, "Pressed: %d", pressedButton);

    LocalPlayer* localPlayer = Main::get().getLocalPlayer();
    localPlayer->guiMessageBox.data = MyGUI::utility::toString(pressedButton);

    PlayerPacket* playerPacket = Main::get().getNetworking()->getPlayerPacket(ID_GUI_MESSAGEBOX);
    playerPacket->setPlayer(Main::get().getLocalPlayer());
    playerPacket->Send();
}

void mwmp::GUIController::WM_UpdateVisible(MWGui::GuiMode mode)
{
    switch((int)mode)
    {
        case GM_TES3MP_InputBox:
        {
            if (mInputBox != 0)
                mInputBox->setVisible(true);
            break;
        }
        case GM_TES3MP_ListBox:
        {
            if (mListBox != 0)
                mListBox->setVisible(true);
            break;
        }
        default:
            break;
    }
}

class MarkerWidget: public MyGUI::Widget
{
MYGUI_RTTI_DERIVED(MarkerWidget)

public:
    void setNormalColour(const MyGUI::Colour& colour)
    {
        mNormalColour = colour;
        setColour(colour);
    }

    void setHoverColour(const MyGUI::Colour& colour)
    {
        mHoverColour = colour;
    }

private:
    MyGUI::Colour mNormalColour;
    MyGUI::Colour mHoverColour;

    void onMouseLostFocus(MyGUI::Widget* _new)
    {
        setColour(mNormalColour);
    }

    void onMouseSetFocus(MyGUI::Widget* _old)
    {
        setColour(mHoverColour);
    }
};

ESM::CustomMarker mwmp::GUIController::createMarker(const RakNet::RakNetGUID &guid)
{
    DedicatedPlayer *player = PlayerList::getPlayer(guid);
    ESM::CustomMarker mEditingMarker;
    if (!player)
    {
        LOG_MESSAGE_SIMPLE(TimedLog::LOG_ERROR, "Unknown player guid: %s", guid.ToString());
        return mEditingMarker;
    }

    mEditingMarker.mNote = player->npc.mName;

    const ESM::Cell *playerCell = &player->cell;

    mEditingMarker.mCell = player->cell.mCellId;

    mEditingMarker.mWorldX = player->position.pos[0];
    mEditingMarker.mWorldY = player->position.pos[1];

    mEditingMarker.mCell.mPaged = playerCell->isExterior();
    if (!playerCell->isExterior())
        mEditingMarker.mCell.mWorldspace = playerCell->mName;
    else
    {
        mEditingMarker.mCell.mWorldspace = ESM::CellId::sDefaultWorldspace;

        // Don't remove these, or the markers will stop showing up in exteriors
        mEditingMarker.mCell.mIndex.mX = playerCell->getGridX();
        mEditingMarker.mCell.mIndex.mY = playerCell->getGridY();
    }
    return mEditingMarker;
}


void mwmp::GUIController::updatePlayersMarkers(MWGui::LocalMapBase *localMapBase)
{
    std::vector<MyGUI::Widget*>::iterator markerWidgetIterator = localMapBase->mPlayerMarkerWidgets.begin();
    for (; markerWidgetIterator != localMapBase->mPlayerMarkerWidgets.end(); ++markerWidgetIterator)
        MyGUI::Gui::getInstance().destroyWidget(*markerWidgetIterator);
    localMapBase->mPlayerMarkerWidgets.clear();

    for (int dX = -localMapBase->mCellDistance; dX <= localMapBase->mCellDistance; ++dX)
    {
        for (int dY =-localMapBase->mCellDistance; dY <= localMapBase->mCellDistance; ++dY)
        {
            ESM::CellId cellId;
            cellId.mPaged = !localMapBase->mInterior;
            cellId.mWorldspace = (localMapBase->mInterior ? localMapBase->mPrefix : ESM::CellId::sDefaultWorldspace);
            cellId.mIndex.mX = localMapBase->mCurX+dX;
            cellId.mIndex.mY = localMapBase->mCurY+dY;

            PlayerMarkerCollection::RangeType markers = mPlayerMarkers.getMarkers(cellId);
            for (PlayerMarkerCollection::ContainerType::const_iterator markerIterator = markers.first;
                markerIterator != markers.second; ++markerIterator)
            {
                const ESM::CustomMarker &marker = markerIterator->second;

                MWGui::LocalMapBase::MarkerUserData markerPos (localMapBase->mLocalMapRender);
                MyGUI::IntPoint widgetPos = localMapBase->getMarkerPosition(marker.mWorldX, marker.mWorldY, markerPos);

                MyGUI::IntCoord widgetCoord(widgetPos.left - 8, widgetPos.top - 8, 16, 16);
                MarkerWidget* markerWidget = localMapBase->mLocalMap->createWidget<MarkerWidget>("CustomMarkerButton",
                                                                                   widgetCoord, MyGUI::Align::Default);

                markerWidget->setDepth(0); // Local_MarkerAboveFogLayer
                markerWidget->setUserString("ToolTipType", "Layout");
                markerWidget->setUserString("ToolTipLayout", "TextToolTipOneLine");
                markerWidget->setUserString("Caption_TextOneLine", MyGUI::TextIterator::toTagsString(marker.mNote));
                markerWidget->setNormalColour(MyGUI::Colour(0.6f, 0.6f, 0.6f));
                markerWidget->setHoverColour(MyGUI::Colour(1.0f, 1.0f, 1.0f));
                markerWidget->setUserData(marker);
                markerWidget->setNeedMouseFocus(true);
                //localMapBase->customMarkerCreated(markerWidget);
                localMapBase->mPlayerMarkerWidgets.push_back(markerWidget);
            }
        }
    }
    localMapBase->redraw();
}

void mwmp::GUIController::setGlobalMapMarkerTooltip(MWGui::MapWindow *mapWindow, MyGUI::Widget *markerWidget, int x, int y)
{
    ESM::CellId cellId;
    cellId.mIndex.mX = x;
    cellId.mIndex.mY = y;
    cellId.mWorldspace = ESM::CellId::sDefaultWorldspace;
    cellId.mPaged = true;
    PlayerMarkerCollection::RangeType markers = mPlayerMarkers.getMarkers(cellId);
    std::vector<std::string> destNotes;
    for (PlayerMarkerCollection::ContainerType::const_iterator it = markers.first; it != markers.second; ++it)
        destNotes.push_back(it->second.mNote);

    if (!destNotes.empty())
    {
        MWGui::LocalMapBase::MarkerUserData data (nullptr);
        data.notes = destNotes;
        data.caption = markerWidget->getUserString("Caption_TextOneLine");

        markerWidget->setUserData(data);
        markerWidget->setUserString("ToolTipType", "MapMarker");
    }
    else
        markerWidget->setUserString("ToolTipType", "Layout");
}

void mwmp::GUIController::updateGlobalMapMarkerTooltips(MWGui::MapWindow *mapWindow)
{
    for (const auto &widget : mapWindow->mGlobalMapMarkers)
    {
        const int x = widget.first.first;
        const int y = widget.first.second;
        setGlobalMapMarkerTooltip(mapWindow, widget.second, x, y);
    }
}
