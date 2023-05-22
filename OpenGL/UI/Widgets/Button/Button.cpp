#include "Button.h"

Button::Button(const std::string& p_lable, const ImVec2& p_size, bool p_disable):
	label(p_lable), size(p_size), disable(p_disable)
{
	auto& style = ImGui::GetStyle();

	idleColor = style.Colors[ImGuiCol_Button];
	hoveredColor = style.Colors[ImGuiCol_ButtonHovered];
	clickedColor = style.Colors[ImGuiCol_ButtonActive];
	textColor = style.Colors[ImGuiCol_Text];
}

void Button::_Draw_Impl()
{
	auto& style = ImGui::GetStyle();

	auto defaultIdleColor = style.Colors[ImGuiCol_Button];
	auto defaultHoveredColor = style.Colors[ImGuiCol_ButtonHovered];
	auto defaultClickedColor = style.Colors[ImGuiCol_ButtonActive];
	auto defaultTextColor = style.Colors[ImGuiCol_Text];


	style.Colors[ImGuiCol_Button] = idleColor.toImVec4();
	style.Colors[ImGuiCol_ButtonHovered] = hoveredColor.toImVec4();
	style.Colors[ImGuiCol_ButtonActive] = clickedColor.toImVec4();
	style.Colors[ImGuiCol_Text] = textColor.toImVec4();

	if (ImGui::ButtonEx(label.c_str(), size, disable ? ImGuiButtonFlags_Disabled : 0))
		ClickedEvent.Invoke();

	style.Colors[ImGuiCol_Button] = defaultIdleColor;
	style.Colors[ImGuiCol_ButtonHovered] = defaultHoveredColor;
	style.Colors[ImGuiCol_ButtonActive] = defaultClickedColor;
	style.Colors[ImGuiCol_Text] = defaultTextColor;
}