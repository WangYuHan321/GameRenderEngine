#include "TextSelectable.h"
TextSelectable::TextSelectable(const std::string& p_content,
    bool p_selected, bool p_disabled)
{
}

void TextSelectable::_Draw_Impl()
{
    if (ImGui::Selectable((content + m_widgetID).c_str(), &selected, disabled ? ImGuiSelectableFlags_Disabled : ImGuiSelectableFlags_None))
    {
        ClickedEvent.Invoke(selected);

        if (selected)
            SelectedEvent.Invoke();
        else
            UnselectedEvent.Invoke();
    }
}