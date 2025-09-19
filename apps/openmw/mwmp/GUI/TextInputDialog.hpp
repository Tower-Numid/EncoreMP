#ifndef OPENMW_TEXTINPUTDIALOG_HPP
#define OPENMW_TEXTINPUTDIALOG_HPP

#include "apps/openmw/mwgui/windowbase.hpp"

namespace MWGui
{
    class WindowManager;
}

namespace mwmp
{
    class TextInputDialog : public MWGui::WindowModal
    {
    public:
        TextInputDialog();

        std::string getTextInput() const;
        void setTextInput(const std::string &text);

        void setNextButtonShow(bool shown);
        void setTextLabel(const std::string &label);
        void setTextNote(const std::string &note);

        void setEditPassword(bool value);

        virtual void onOpen();
        virtual bool exit();

        /** Event : Dialog finished, OK button clicked.\n
            signature : void method()\n
        */
        EventHandle_WindowBase eventDone;

    protected:
        void onOkClicked(MyGUI::Widget *_sender);
        void onTextAccepted(MyGUI::Edit *_sender);

    private:
        MyGUI::EditBox *mTextEdit;
    };
}


#endif //OPENMW_TEXTINPUTDIALOG_HPP
