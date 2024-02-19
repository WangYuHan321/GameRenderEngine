#pragma once
#include "APanel.h"
#include "../Internel/UI_Common.h"
class APanelTransformable :
    public APanel
{
public:
    APanelTransformable(
        const ImVec2& p_defaultPos = ImVec2(-1.f, -1.f),
        const ImVec2& p_defaultSize = ImVec2(-1.f, -1.f),
        HorizontalAlignment p_defaultHorizontalAlignment = HorizontalAlignment::Left,
        VerticalAlignment p_defaultVerticalAlignment = VerticalAlignment::Top,
        bool p_ignoreConfigFile = false);


protected:
    void Update();
    virtual void _Draw_Impl() = 0;

    ImVec2 GetSize() const;

private:
    ImVec2 CalculatePositionAlignmebtOffset(bool p_default = false);

    void UpdatePosition();
    void UpdateSize();

    void CopyImGuiPosition();
    void CopyImGuiSize();


public:
    bool autoSize = true;

protected:
    
    bool m_positionChanged = false;
    bool m_sizeChanged = false;
    
    bool m_ignoreConfigFile = false;
    
    bool m_alignmentChanged = false;
    bool m_firstFrame = true;

    //default
    ImVec2 m_defaultPosition;
    ImVec2 m_defaultSize;

    HorizontalAlignment m_defaultHorizontalAlignment;
    VerticalAlignment m_defaultVerticalAlignment;


    ImVec2 m_position = ImVec2(0.0f, 0.0f);
    ImVec2 m_size = ImVec2(0.0f, 0.0f);

    HorizontalAlignment m_horizontalAlignment = HorizontalAlignment::Left;
    VerticalAlignment m_verticalAlignment = VerticalAlignment::Top;
};

