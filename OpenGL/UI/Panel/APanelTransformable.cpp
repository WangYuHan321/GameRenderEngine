#include "APanelTransformable.h"

extern ImVec2 AddVector2(const ImVec2& left, const ImVec2& right);

APanelTransformable::APanelTransformable(
    const ImVec2& p_defaultPos,
    const ImVec2& p_defaultSize,
    HorizontalAlignment p_defaultHorizontalAlignment,
    VerticalAlignment p_defaultVerticalAlignment,
    bool p_ignoreConfigFile):
    m_defaultPosition(p_defaultPos),
    m_defaultSize(p_defaultSize),
    m_defaultHorizontalAlignment(p_defaultHorizontalAlignment),
    m_defaultVerticalAlignment(p_defaultVerticalAlignment),
    m_ignoreConfigFile(p_ignoreConfigFile),
    APanel()
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

ImVec2 APanelTransformable::CalculatePositionAlignmebtOffset(bool p_default)
{
    ImVec2 result(0.0f, 0.0f);

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

ImVec2 APanelTransformable::GetSize() const
{
    return m_size;
}

void APanelTransformable::UpdatePosition()
{
    if (m_defaultPosition.x != -1.f && m_defaultPosition.y != 1.f)
    {
        ImVec2 offsettedDefaultPos = AddVector2(m_defaultPosition, CalculatePositionAlignmebtOffset(true));
        ImGui::SetWindowPos(offsettedDefaultPos, m_ignoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
    }

    if (m_positionChanged || m_alignmentChanged)
    {
        ImVec2 offset = CalculatePositionAlignmebtOffset(false);
        ImVec2 offsettedPos(m_position.x + offset.x, m_position.y + offset.y);
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


