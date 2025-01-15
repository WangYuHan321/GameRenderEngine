#pragma once
#include "Sample.h"

namespace CEGUI
{
    class SubscriberSlot;
}

// Sample class
class SampleEditor : public Sample
{
public:
    SampleEditor();
    virtual ~SampleEditor() {}

    // method to initialse the samples windows and events.
    bool initialise(CEGUI::GUIContext* guiContext) override;
    // method to perform any required cleanup operations.
    void deinitialise() override;

private:
    // creates the menubar with content
    void createMenu(CEGUI::Window* bar);

    // quit menu item handler
    bool fileQuit(const CEGUI::EventArgs&);

    // new dialog menu item handler
    bool addNewChild(const CEGUI::EventArgs& e);
    bool keyDownEventHandler(const CEGUI::EventArgs& e);

    CEGUI::ScrollablePane* d_pane = nullptr;
};
