#pragma once
#include "Text.h"
#include "../../Event/Event.h"
class TextSelectable :
    public Text
{
public:
    TextSelectable(const std::string& p_content, 
        bool p_selected = false, bool p_disabled = false);

protected:
    virtual void _Draw_Impl() override;

public:
    bool selected;
    bool disabled;

    Event<bool> ClickedEvent;
    Event<> SelectedEvent;
    Event<> UnselectedEvent;
};

