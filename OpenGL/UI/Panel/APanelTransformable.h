#pragma once
#include "APanel.h"
#include "../Internel/UI_Common.h"
class APanelTransformable :
    public APanel
{
public:
    APanelTransformable(
        const Vector2& p_defaultPos = Vector2(-1.f, -1.f),
        const Vector2& p_defaultSize = Vector2(-1.f, -1.f),
        HorizontalAlignment p_defaultHorizontalAlignment = HorizontalAlignment::Left,
        VerticalAlignment p_defaultVerticalAlignment = VerticalAlignment::Top,
        bool p_ignoreConfigFile = false);


protected:
    void Update();
    virtual void _Draw_Impl() = 0;

    Vector2 GetSize() const;

private:
    Vector2 CalculatePositionAlignmebtOffset(bool p_default = false);

    void UpdatePosition();
    void UpdateSize();

    void CopyImGuiPosition();
    void CopyImGuiSize();


protected:

    bool m_sizeChanged = false;
    bool m_positionChanged = false;
    bool m_alignmentChanged = false;
    bool m_ignoreConfigFile = false;
    bool m_firstFrame = true;
    bool autoSize = true;

    //default
    Vector2 m_defaultPosition;
    Vector2 m_defaultSize;

    HorizontalAlignment m_defaultHorizontalAlignment;
    VerticalAlignment m_defaultVerticalAlignment;


    // normal
    Vector2 m_position;
    Vector2 m_size;

    HorizontalAlignment m_horizontalAlignment = HorizontalAlignment::Left;
    VerticalAlignment m_verticalAlignment = VerticalAlignment::Top;
};

