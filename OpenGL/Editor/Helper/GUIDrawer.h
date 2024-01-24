#pragma once

#include "../../Util/common.h"
class Texture;
class WidgetContainer;


class GUIDrawer 
{
public:

	static Color4 titleColor;
	static Color4 clearBtnColor;

	static float _MIN_FLOAT;
	static float _MAX_FLOAT;

	static void ProvideEmptyTexture(Texture& p_emptyTexture);

	static void CreateTitle(WidgetContainer& p_root, string& p_name);




private:
	static Texture* __EMPTY_TEXTURE;

};

