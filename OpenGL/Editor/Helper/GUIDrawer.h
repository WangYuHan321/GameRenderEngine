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

	static void DrawVec3(WidgetContainer& p_root, const std::string& p_name, std::function<Vector3(void)> p_gatherer, std::function<void(Vector3)> p_provider, float p_step, float p_min, float p_max);



private:
	static Texture* __EMPTY_TEXTURE;

};

