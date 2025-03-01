#pragma once

#include "AButton.h"
#include "../../Internel/UI_Common.h"

class ButtonImage : 
	public AButton
{
public:
	ButtonImage(uint32_t p_textureID, const ImVec2& p_size, int padding = -1);

protected:
	void _Draw_Impl() override;

public:
	//是否开启按钮一直按住不松
	bool disabled = false;

	Color4 background = { 0,0,0,0 };
	Color4 tint = { 1,1,1,1 };

	UTextureID textureID;
	ImVec2 size;
	int framePadding;
};

