#ifndef OPENMW_GUILOGIN_HPP
#define OPENMW_GUILOGIN_HPP

#include "apps/openmw/mwgui/windowbase.hpp"

class GUILogin : public MWGui::WindowModal
{
public:
    GUILogin();

    MyGUI::EditBox* mLogin;
    MyGUI::EditBox* mServer;
    MyGUI::EditBox* mPort;
protected:
    MyGUI::Button* mConnect;
};


#endif //OPENMW_GUILOGIN_HPP
