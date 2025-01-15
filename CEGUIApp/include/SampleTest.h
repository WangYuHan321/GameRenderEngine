#pragma once
#include "Sample.h"

namespace CEGUI
{
    class SubscriberSlot;
}

// Sample class
class SampleTest : public Sample
{
public:
    SampleTest();
    virtual ~SampleTest() {}

    // method to initialse the samples windows and events.
    bool initialise(CEGUI::GUIContext* guiContext) override;

    // method to perform any required cleanup operations.
    void deinitialise() override;

private:
    /** Sub routines for each edit panel.*/
    void initStaticText();
    void initSingleLineEdit();
    void initMultiLineEdit();
    /** Sets group- and selected for given radio name.*/
    void initRadio(const CEGUI::String& radio, int group, bool selected);
    /** Generic subscribe helper.*/
    void subscribeEvent(const CEGUI::String& widgetName, const CEGUI::String& eventName, const CEGUI::SubscriberSlot& method);
    /** Returns whether the given radio is selected.*/
    bool isRadioSelected(const CEGUI::String& radio);
    /** Returns whether the given checkbox is selected.*/
    bool isCheckboxSelected(const CEGUI::String& checkbox);
    /** Called when user changes the formatting option of the static text.*/
    bool formatChangedHandler(const CEGUI::EventArgs& e);
    /** Called when user changes the scrollbar option of the multiline edit.*/
    bool vertScrollChangedHandler(const CEGUI::EventArgs& e);
    /** Called when the user clicks the Quit button.*/
    bool quit(const CEGUI::EventArgs& e);
};
