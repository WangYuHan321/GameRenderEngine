#include "GUIDrawer.h"
#include "../../UI/Internel/WidgetContainer.h"
#include "../../UI/Widgets/Text/TextColored.h"
#include "../../UI/Widgets/Drag/DragMultipleScalars.h"
#include "../../Render/Shader/Texture.h"
#include "../../Render/Mesh/Material.h"
#include "../../UI/Layout/Group.h"
#include "../../UI/Plugin/DDTarget.h"
#include "../../UI/Widgets/Text/Text.h"
#include "../../Render/Shader/EShader.h"
#include "../../UI/Visual/Image.h"
#include "../../UI/Widgets/Button/Button.h"
#include "../../UI/Widgets/Selection/ColorEdit.h"
#include "../../UI/Widgets/Selection/CheckBox.h"
#include "../../UI/Widgets/Selection/ComboBox.h"
#include "../../File/Path/PathParser.h"
#include "../../Global/ServiceLocator.h"
#include"../../Render/Resource/MaterialManager.h"
#include"../../Render/Resource/ShaderManager.h"
#include"../../Render/Resource/TextureManager.h"
#include "../../File/XmlManager.h"

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
	CreateTitle(p_root, p_name);
	auto& item = p_root.CreateWidget<CheckBox>();
	item.value = p_data;

	item.ValueChangedEvent += [&p_data](bool it) { 
		p_data = it;
	};
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

void GUIDrawer::DrawColor(WidgetContainer& p_root, const std::string& p_name, Color3& p_color, bool p_hasAlpha)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<ColorEdit>(p_hasAlpha);
	auto& dispatcher = widget.AddPlugin<DataDispatcher<Color3>>();
	dispatcher.RegisterReference(p_color);
}

void GUIDrawer::DrawColor(WidgetContainer& p_root, const std::string& p_name, Color4& p_color, bool p_hasAlpha)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<ColorEdit>(p_hasAlpha);
	auto& dispatcher = widget.AddPlugin<DataDispatcher<Color4>>();
	dispatcher.RegisterReference(p_color);
}

Text& GUIDrawer::DrawMaterial(WidgetContainer& p_root, const std::string& p_name, Material*& p_data, Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);
	std::string displayText = p_data ? p_data->Path : GLOBALSERVICE(XmlManager).GetLanguage(EMPTY_TEXT);

	auto& rightSide = p_root.CreateWidget<Group>();
	auto& textEdit = rightSide.CreateWidget<Text>(displayText);

	textEdit.AddPlugin<DDTarget<std::pair<std::string, Group*>>>("File").DataReceivedEvent += [&textEdit, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (PathParser::getInstance()->GetFileType(p_receivedData.first) == EFileType::MATERIAL)
		{
			std::string fileName = PathParser::getInstance()->GetFileNameByPath(p_receivedData.first);
			if (auto resource = ServiceLocator::getInstance()->Get<MaterialManager>()[fileName]; resource)
			{
				p_data = resource;
				textEdit.content = fileName;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	textEdit.lineBreak = false;

	auto& resetBtn = rightSide.CreateWidget<Button>(GLOBALSERVICE(XmlManager).GetLanguage(MATERIAL_EDITOR_RESET));
	resetBtn.idleColor = Color4{ 0.5f, 0.0f, 0.0f, 1.0f };
	resetBtn.ClickedEvent += [&textEdit, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		textEdit.content = GLOBALSERVICE(XmlManager).GetLanguage(EMPTY_TEXT);
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return textEdit;
}

Text& GUIDrawer::DrawShader(WidgetContainer& p_root, const std::string& p_name, CShader*& p_data, Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);
	std::string displayText = p_data ? p_data->GetShaderPath() : GLOBALSERVICE(XmlManager).GetLanguage(EMPTY_TEXT);

	auto& rightSide = p_root.CreateWidget<Group>();
	auto& textEdit = rightSide.CreateWidget<Text>();
	textEdit.content = displayText;
	
	textEdit.AddPlugin<DDTarget<std::pair<std::string, Group*>>>("File").DataReceivedEvent += [&textEdit, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (PathParser::getInstance()->GetFileType(p_receivedData.first) == EFileType::SHADER)
		{
			std::string fileName = PathParser::getInstance()->GetFileNameByPath(p_receivedData.first);
			if (auto resource = ServiceLocator::getInstance()->Get<ShaderManager>()[fileName]; resource)
			{
				p_data = resource;
				textEdit.content = fileName;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	textEdit.lineBreak = false;

	auto& resetBtn = rightSide.CreateWidget<Button>(GLOBALSERVICE(XmlManager).GetLanguage(MATERIAL_EDITOR_RESET));
	resetBtn.idleColor = Color4{ 0.5f, 0.0f, 0.0f, 1.0f };
	resetBtn.ClickedEvent += [&textEdit, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		textEdit.content = GLOBALSERVICE(XmlManager).GetLanguage(EMPTY_TEXT);
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return textEdit;
}

Image& GUIDrawer::DrawTexture(WidgetContainer& p_root, const std::string& p_name, Texture*& p_data, Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	auto& item = p_root.CreateWidget<Group>();

	auto& widget = item.CreateWidget<Image>(p_data ? p_data->ID : 0, ImVec2(75,75));
	
	widget.AddPlugin<DDTarget<std::pair<std::string, Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_dataReceive)
	{
		std::string fileName = PathParser::getInstance()->GetFileNameByPath(p_dataReceive.first);
		if (auto resource = ServiceLocator::getInstance()->Get<TextureManager>()[fileName]; resource)
		{
			p_data = resource;
			widget.textureID.ID = p_data->ID;
			if (p_updateNotifier)
				p_updateNotifier->Invoke();
		}
	};

	widget.lineBreak = false;

	auto& resetBuuton = item.CreateWidget<Button>(GLOBALSERVICE(XmlManager).GetLanguage(CLEAR_TEXT));
	resetBuuton.idleColor = Color4(0.5f, 0.0f, 0.0f, 1.0f);
	resetBuuton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.textureID.ID = 0;
		if(p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
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

 void GUIDrawer::DrawColor(WidgetContainer& p_root, const std::string& p_name, std::function<Color3(void)> p_gatherer, std::function<void(Color3)> p_provider, bool p_hasAlpha)
 {

 }

void GUIDrawer::DrawColor(WidgetContainer& p_root, const std::string& p_name, std::function<Color4(void)> p_gatherer, std::function<void(Color4)> p_provider, bool p_hasAlpha)
 {
 }

//void GUIDrawer::DrawCombox(WidgetContainer& p_root, const std::string& p_name, DepthFunc& p_depthTest)
//{
//	CreateTitle(p_root, p_name);
//	auto& item = p_root.CreateWidget<ComboBox>(7);
//
//	item.choices[0] = "OpenGL_LESS";
//	item.choices[1] = "OpenGL_NEVER";
//	item.choices[2] = "OpenGL_EQUAL";
//	item.choices[3] = "OpenGL_GREATER";
//	item.choices[4] = "OpenGL_NOTEQUAL";
//	item.choices[5] = "OpenGL_GEQUAL";
//	item.choices[6] = "OpenGL_ALWAYS";
//
//	item.ValueChangedEvent += [&p_depthTest](int id)
//	{
//		switch (id)
//		{
//			case 0: p_depthTest = DepthFunc::OpenGL_LESS; break;
//			case 1: p_depthTest = DepthFunc::OpenGL_NEVER; break;
//			case 2: p_depthTest = DepthFunc::OpenGL_EQUAL; break;
//			case 3: p_depthTest = DepthFunc::OpenGL_GREATER; break;
//			case 4: p_depthTest = DepthFunc::OpenGL_NOTEQUAL; break;
//			case 5: p_depthTest = DepthFunc::OpenGL_GEQUAL; break;
//			case 6: p_depthTest = DepthFunc::OpenGL_ALWAYS; break;
//		}
//	};
//}
//
//void GUIDrawer::DrawCombox(WidgetContainer& p_root, const std::string& p_name, BlendParam& p_blendParam)
//{
//	CreateTitle(p_root, p_name);
//
//	auto& item = p_root.CreateWidget<ComboBox>(7);
//	item.choices[0] = "OpenGL_ZERO";
//	item.choices[1] = "OpenGL_ONE";
//	item.choices[2] = "OpenGL_SRC_COLOR";
//	item.choices[3] = "OpenGL_ONE_MINUS_SRC_COLOR";
//	item.choices[4] = "OpenGL_DST_COLOR";
//	item.choices[5] = "OpenGL_ONE_MINUS_DST_COLOR";
//	item.choices[6] = "OpenGL_SRC_ALPHA";
//	item.choices[7] = "OpenGL_ONE_MINUS_SRC_ALPHA";
//	item.choices[8] = "OpenGL_DST_ALPHA";
//	item.choices[9] = "OpenGL_ONE_MINUS_DST_ALPHA";
//	item.choices[10] = "OpenGL_CONSTANT_COLOR";
//	item.choices[11] = "OpenGL_ONE_MINUS_CONSTANT_COLOR";
//	item.choices[12] = "OpenGL_CONSTANT_ALPHA";
//	item.choices[13] = "OpenGL_ONE_MINUS_CONSTANT_ALPHA";
//	item.choices[14] = "OpenGL_SRC_ALPHA_SATURATE";
//
//	item.ValueChangedEvent += [&p_blendParam](int id)
//	{
//		switch (id)
//		{
//		case 0: p_blendParam = BlendParam::OpenGL_ZERO; break;
//		case 1: p_blendParam = BlendParam::OpenGL_ONE; break;
//		case 2: p_blendParam = BlendParam::OpenGL_SRC_COLOR; break;
//		case 3: p_blendParam = BlendParam::OpenGL_ONE_MINUS_SRC_COLOR; break;
//		case 4: p_blendParam = BlendParam::OpenGL_DST_COLOR; break;
//		case 5: p_blendParam = BlendParam::OpenGL_ONE_MINUS_DST_COLOR; break;
//		case 6: p_blendParam = BlendParam::OpenGL_SRC_ALPHA; break;
//		case 7: p_blendParam = BlendParam::OpenGL_ONE_MINUS_SRC_ALPHA; break;
//		case 8: p_blendParam = BlendParam::OpenGL_DST_ALPHA; break;
//		case 9: p_blendParam = BlendParam::OpenGL_ONE_MINUS_DST_ALPHA; break;
//		case 10: p_blendParam = BlendParam::OpenGL_CONSTANT_COLOR; break;
//		case 11: p_blendParam = BlendParam::OpenGL_ONE_MINUS_CONSTANT_COLOR; break;
//		case 12: p_blendParam = BlendParam::OpenGL_CONSTANT_ALPHA; break;
//		case 13: p_blendParam = BlendParam::OpenGL_ONE_MINUS_CONSTANT_ALPHA; break;
//		case 14: p_blendParam = BlendParam::OpenGL_SRC_ALPHA_SATURATE; break;
//		}
//	};
//}
//
//void GUIDrawer::DrawCombox(WidgetContainer& p_root, const std::string& p_name, BlendFunc& p_blendFunc)
//{
//	CreateTitle(p_root, p_name);
//	auto& item = p_root.CreateWidget<ComboBox>(5);
//	item.choices[0] = "OpenGL_FUNC_ADD";
//	item.choices[1] = "OpenGL_FUNC_SUBTRACT";
//	item.choices[2] = "OpenGL_FUNC_REVERSE_SUBTRACT";
//	item.choices[3] = "OpenGL_MIN";
//	item.choices[4] = "OpenGL_MAX";
//
//	item.ValueChangedEvent += [&p_blendFunc](int id)
//	{
//		switch (id)
//		{
//		case 0: p_blendFunc = BlendFunc::OpenGL_FUNC_ADD; break;
//		case 1: p_blendFunc = BlendFunc::OpenGL_FUNC_SUBTRACT; break;
//		case 2: p_blendFunc = BlendFunc::OpenGL_FUNC_REVERSE_SUBTRACT; break;
//		case 3: p_blendFunc = BlendFunc::OpenGL_MIN; break;
//		case 4: p_blendFunc = BlendFunc::OpenGL_MAX; break;
//		}
//	};
//}
//
//void GUIDrawer::DrawCombox(WidgetContainer& p_root, const std::string& p_name, CullFace& p_cullFace)
//{
//	CreateTitle(p_root, p_name);
//	auto& item = p_root.CreateWidget<ComboBox>(3);
//	item.choices[0] = "OpenGL_FRONT";
//	item.choices[1] = "OpenGL_BACK";
//	item.choices[2] = "OpenGL_FRONT_AND_BACKT";
//
//	item.ValueChangedEvent += [&p_cullFace](int id)
//	{
//		switch (id)
//		{
//		case 0: p_cullFace = CullFace::OpenGL_FRONT; break;
//		case 1: p_cullFace = CullFace::OpenGL_BACK; break;
//		case 2: p_cullFace = CullFace::OpenGL_FRONT_AND_BACKT; break;
//		}
//	};
//}
//
//void GUIDrawer::DrawCombox(WidgetContainer& p_root, const std::string& p_name, FrontFace& p_frontFace)
//{
//	CreateTitle(p_root, p_name);
//	auto& item = p_root.CreateWidget<ComboBox>(2);
//	item.choices[0] = "OpenGL_CW";
//	item.choices[1] = "OpenGL_CCW";
//
//	item.ValueChangedEvent += [&p_frontFace](int id)
//	{
//		switch (id)
//		{
//		case 0: p_frontFace = FrontFace::OpenGL_CW; break;
//		case 1: p_frontFace = FrontFace::OpenGL_CCW; break;
//		}
//	};
//}
