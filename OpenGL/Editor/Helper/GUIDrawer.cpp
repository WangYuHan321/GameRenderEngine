#include "GUIDrawer.h"
#include "../../UI/Internel/WidgetContainer.h"
#include "../../UI/Widgets/Text/TextColored.h"
#include "../../Render/Shader/Texture.h"

Color4 GUIDrawer::titleColor = { 0.85f, 0.65f, 0.0f, 1.0f };
Color4 GUIDrawer::clearBtnColor = { 0.5f, 0.0f, 0.0f, 1.0f };
float GUIDrawer::_MIN_FLOAT = -999999999.f;
float GUIDrawer::_MAX_FLOAT = +999999999.f;
Texture* GUIDrawer::__EMPTY_TEXTURE = nullptr;


void GUIDrawer::ProvideEmptyTexture(Texture& p_emptyTexture)
{
	__EMPTY_TEXTURE = &p_emptyTexture;
}

void GUIDrawer::CreateTitle(WidgetContainer& p_root, string& p_name)
{
	p_root.CreateWidget<TextColored>(p_name, titleColor);
}

void GUIDrawer::DrawVec3(WidgetContainer& p_root, const std::string& p_name, std::function<Vector3(void)> p_gatherer, std::function<void(Vector3)> p_provider, float p_step, float p_min, float p_max)
{

}