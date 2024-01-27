#include "Image.h"

Image::Image(uint32_t p_textureID, const ImVec2& p_size):
	textureID{ p_textureID },size(p_size)
{

}

void Image::_Draw_Impl()
{
	ImGui::Image(textureID.raw, size, ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
}