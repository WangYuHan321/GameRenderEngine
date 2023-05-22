#include "TextColored.h"

TextColored::TextColored(const std::string& p_content,
	const Color4& p_color ):
	Text(p_content), color(p_color)
{
}

void TextColored::_Draw_Impl()
{
	ImGui::TextColored(color.toImVec4(), content.c_str());
}