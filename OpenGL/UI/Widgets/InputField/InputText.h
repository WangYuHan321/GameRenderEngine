#pragma once
#include "../DataWidget.h"
#include "../../Event/Event.h"

class InputText :
    public DataWidget<std::string>
{
public:
    InputText(const std::string& p_content = "", const std::string& p_label = "");

protected:

    void _Draw_Impl() override;

public:
    std::string content;
    std::string label;
    bool selectAllOnClick = false;
    Event<string> ContentChangedEvent;
    Event<string> EnterPressedEvent;

};

