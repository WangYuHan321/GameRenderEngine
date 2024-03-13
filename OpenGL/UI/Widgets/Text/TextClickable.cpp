#include "TextClickable.h"


TextClickable::TextClickable(const std::string content):
	Text(content)
{
}

void TextClickable::_Draw_Impl()
{
    bool useless = false;

    if (ImGui::Selectable((content + m_widgetID).c_str(), &useless, ImGuiSelectableFlags_AllowDoubleClick))
    {
        if (ImGui::IsMouseDoubleClicked(0))
        {
            DoubleClickedEvent.Invoke();
        }
        else
        {
            ClickedEvent.Invoke();
        }
    }
}