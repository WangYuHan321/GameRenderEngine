#include "APanelTransformable.h"

extern Vector2 AddVector2(const Vector2& left, const Vector2& right);

APanelTransformable::APanelTransformable(
    const Vector2& p_defaultPos,
    const Vector2& p_defaultSize,
    HorizontalAlignment p_defaultHorizontalAlignment,
    VerticalAlignment p_defaultVerticalAlignment,
    bool p_ignoreConfigFile):
    m_defaultPosition(p_defaultPos),
    m_defaultSize(p_defaultSize),
    m_defaultHorizontalAlignment(p_defaultHorizontalAlignment),
    m_defaultVerticalAlignment(p_defaultVerticalAlignment),
    m_ignoreConfigFile(p_ignoreConfigFile)
{
}

void APanelTransformable::Update()
{
    if (!m_firstFrame)
    {
        if (!autoSize)
            UpdateSize();
        CopyImGuiSize();

        UpdatePosition();
        CopyImGuiPosition();
    }

    m_firstFrame = false;
}

Vector2 APanelTransformable::CalculatePositionAlignmebtOffset(bool p_default)
{
    Vector2 result(0.0f, 0.0f);

    switch (p_default ? m_defaultHorizontalAlignment : m_horizontalAlignment)
    {
    case HorizontalAlignment::Center:
        result.x -= m_size.x / 2.0f;
        break;
    case HorizontalAlignment::Right:
        result.x -= m_size.x / 2.0f;
        break;
    }

    switch (p_default ? m_defaultVerticalAlignment : m_verticalAlignment)
    {
    case VerticalAlignment::Middle:
        result.y -= m_size.y / 2.0f;
        break;
    case VerticalAlignment::Bottom:
        result.y -= m_size.y;
        break;
    }
    return result;
}

void APanelTransformable::CopyImGuiPosition()
{
    m_position = ImGui::GetWindowPos();
}

void APanelTransformable::CopyImGuiSize()
{
    m_size = ImGui::GetWindowSize();
}

void APanelTransformable::UpdatePosition()
{
    if (m_defaultPosition.x != -1.f && m_defaultPosition.y != 1.f)
    {
        Vector2 offsettedDefaultPos = AddVector2(m_defaultPosition, CalculatePositionAlignmebtOffset(true));
        ImGui::SetWindowPos(offsettedDefaultPos, m_ignoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
    }

    if (m_positionChanged || m_alignmentChanged)
    {
        Vector2 offset = CalculatePositionAlignmebtOffset(false);
        Vector2 offsettedPos(m_position.x + offset.x, m_position.y + offset.y);
        ImGui::SetWindowPos(offsettedPos, ImGuiCond_Always);
        m_positionChanged = false;
        m_alignmentChanged = false;
    }
}

void APanelTransformable::UpdateSize()
{
    if (m_sizeChanged)
    {
        ImGui::SetWindowSize(m_size, ImGuiCond_Always);
    }
}


