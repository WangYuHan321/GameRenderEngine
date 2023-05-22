#include "ButtonImage.h"

ButtonImage::ButtonImage(uint32_t p_textureID, const ImVec2& p_size):
	textureID{ p_textureID }, size(p_size)
{
}

void ButtonImage::_Draw_Impl()
{
	ImVec4 bg = background.toImVec4();
	ImVec4 tn = tint.toImVec4();

	if (ImGui::ImageButton(textureID.raw, size, ImVec2(0.f, 1.f), ImVec2(1.f, 0.f), -1, bg, tn, disabled ? ImGuiButtonFlags_Disabled : 0))
		ClickedEvent.Invoke();
}