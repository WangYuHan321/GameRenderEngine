#include "Text.h"


Text::Text(const string& p_content):
	DataWidget<string>(content),
	content(p_content)
{
}

void Text::_Draw_Impl()
{
	ImGui::Text(content.c_str());
}