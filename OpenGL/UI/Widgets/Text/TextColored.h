#pragma once
#include"Text.h"

class TextColored : public Text
{
public:
	TextColored(const std::string& p_content = "",
		const Color4& p_color = Color4(1.0f, 1.0f, 1.0f, 1.0f));

public:
	Color4 color;

protected:
	virtual void _Draw_Impl() override;
};

