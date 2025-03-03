#pragma once

#include "APanelTransformable.h"
#include "../../Event/Event.h"
#include "../../UI/Internel/UI_Common.h"

class PanelWindow :
    public APanelTransformable
{
public:
    PanelWindow(const std::string& p_name = "",
        bool m_opened = true,
        const PanelWindowSetting& p_panelSetting = PanelWindowSetting{});


    void Open();
    void Close();
    void SetOpened(bool p_value);
    
    void ScrollToBottom() { m_mustScrollToBottom = true; }
    void ScrollToTop() { m_mustScrollToTop = true; }
    bool IsHovered()const { return m_hovered; }
    bool IsFocused()const { return m_focused; }
    bool IsOpened() const { return m_opened;  }

    Event<>OpenEvent;
    Event<>CloseEvent;
protected:
    void _Draw_Impl();

public:
    
    std::string name;

    ImVec2 minSize = { 0.0f, 0.0f };
    ImVec2 maxSize = { 0.0f,0.0f };

    bool resizeable = true;
    bool closeable = false;
    bool movable = false;
    bool dockable = false;
    bool hideBackground = false;
    bool forceHorizontalScrollbar = false;
    bool forceVerticalScrollbar = false;
    bool allowHorizontalScrollbar = false;
    bool bringToFrontOnFocus = false;
    bool collapsable = false;
    bool allowInputs = false;
    bool scrollable = false;
    bool titleBar = true;

private:

    bool m_scrolledToBottom = false;
    bool m_scrolledToTop = false;
    bool m_mustScrollToBottom = false;
    bool m_mustScrollToTop = false;

    bool m_opened;
    bool m_hovered;
    bool m_focused;
};

