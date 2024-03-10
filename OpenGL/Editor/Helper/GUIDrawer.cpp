#include "GUIDrawer.h"
#include "../../UI/Internel/WidgetContainer.h"
#include "../../UI/Widgets/Text/TextColored.h"
#include "../../UI/Widgets/Drag/DragMultipleScalars.h"
#include "../../Render/Shader/Texture.h"
#include "../../UI/Widgets/Selection/ColorEdit.h"

Color4 GUIDrawer::titleColor = { 0.85f, 0.65f, 0.0f, 1.0f };
Color4 GUIDrawer::clearBtnColor = { 0.5f, 0.0f, 0.0f, 1.0f };
float GUIDrawer::_MIN_FLOAT = -999999999.f;
float GUIDrawer::_MAX_FLOAT = +999999999.f;
Texture* GUIDrawer::__EMPTY_TEXTURE = nullptr;


void GUIDrawer::ProvideEmptyTexture(Texture& p_emptyTexture)
{
	__EMPTY_TEXTURE = &p_emptyTexture;
}

void GUIDrawer::CreateTitle(WidgetContainer& p_root, const string& p_name)
{
	p_root.CreateWidget<TextColored>(p_name, titleColor);
}

void GUIDrawer::DrawBoolean(WidgetContainer& p_root, const std::string& p_name, bool& p_data)
{
	//CreateTitle(p_root, p_name);
	//auto& widget = p_root.CreateWidget<CheckBox>();
	//auto& dispatcher = widget.AddPlugin<DataDispatcher<bool>>();
	//dispatcher.RegisterReference(reinterpret_cast<bool&>(p_data));
}
void GUIDrawer::DrawVec2(WidgetContainer& p_root, const std::string& p_name, Vector2& p_data, float p_step, float p_min, float p_max)
{

}

void GUIDrawer::DrawVec3(WidgetContainer& p_root, const std::string& p_name, Vector3& p_data, float p_step, float p_min, float p_max)
{

}
void GUIDrawer::DrawVec4(WidgetContainer& p_root, const std::string& p_name, Vector4& p_data, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<DragMultipleScalars<float, 4>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<DataDispatcher<std::array<float, 4>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 4>&>(p_data));
}

void GUIDrawer::DrawQuat(WidgetContainer& p_root, const std::string& p_name, Quaternion& p_data, float p_step, float p_min, float p_max)
{

}

void GUIDrawer::DrawString(WidgetContainer& p_root, const std::string& p_name, std::string& p_data)
{

}

void GUIDrawer::DrawColor4(WidgetContainer& p_root, const std::string& p_name, Color4& p_color, bool p_hasAlpha)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<ColorEdit>(p_hasAlpha);
	auto& dispatcher = widget.AddPlugin<DataDispatcher<Color4>>();
	dispatcher.RegisterReference(p_color);
}

void GUIDrawer::DrawBoolean(WidgetContainer& p_root, const std::string& p_name, std::function<bool(void)> p_gatherer, std::function<void(bool)> p_provider)
{

}

void GUIDrawer::DrawVec2(WidgetContainer& p_root, const std::string& p_name, std::function<Vector2(void)> p_gatherer, std::function<void(Vector2)> p_provider, float p_step , float p_min , float p_max)
{

}

void GUIDrawer::DrawVec3(WidgetContainer& p_root, const std::string& p_name, std::function<Vector3(void)> p_gatherer, std::function<void(Vector3)> p_provider, float p_step , float p_min , float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<DragMultipleScalars<float, 3>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<DataDispatcher<std::array<float, 3>>>();

	dispatcher.RegisterGatherer([p_gatherer]()
		{
			Vector3 value = p_gatherer();
			return reinterpret_cast<const std::array<float, 3>&>(value);
		});

	dispatcher.RegisterProvider([p_provider](std::array<float, 3> p_value)
		{
			p_provider(reinterpret_cast<Vector3&>(p_value));
		});
}

void GUIDrawer::DrawVec4(WidgetContainer& p_root, const std::string& p_name, std::function<Vector4(void)> p_gatherer, std::function<void(Vector4)> p_provider, float p_step , float p_min, float p_max )
{

}
void GUIDrawer::DrawQuat(WidgetContainer& p_root, const std::string& p_name, std::function<Quaternion(void)> p_gatherer, std::function<void(Quaternion)> p_provider, float p_step, float p_min, float p_max)
{

}

 void GUIDrawer::DrawString(WidgetContainer& p_root, const std::string& p_name, std::function<std::string(void)> p_gatherer, std::function<void(std::string)> p_provider)
 {

 }

 void GUIDrawer::DrawColor4(WidgetContainer& p_root, const std::string& p_name, std::function<Color4(void)> p_gatherer, std::function<void(Color4)> p_provider, bool p_hasAlpha)
 {

 }