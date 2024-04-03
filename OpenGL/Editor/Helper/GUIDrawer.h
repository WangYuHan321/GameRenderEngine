#pragma once

#include "../../Util/common.h"
#include "../../Render/Material/MaterialEditorType.h"

#undef min
#undef max

#include <limits.h>
#include "../../Event/Event.h"

class Text;
class Image;
class CShader;
class Texture;
class Material;
class UniformSampler;
class WidgetContainer;


class GUIDrawer 
{
public:

	static Color4 titleColor;
	static Color4 clearBtnColor;

	static float _MIN_FLOAT;
	static float _MAX_FLOAT;

	static void ProvideEmptyTexture(Texture& p_emptyTexture);
	static Texture* GetEmptyTexture();

	static void CreateTitle(WidgetContainer& p_root,const string& p_name);

	template <typename T>
	static void DrawScalar(WidgetContainer& p_root, const std::string& p_name, T& p_data, float p_step = 1.0f, T p_min = std::numeric_limits<T>::min(), T p_max = std::numeric_limits<T>::max());

	static void DrawBoolean(WidgetContainer& p_root, const std::string& p_name, bool& p_data);
	static void DrawVec2(WidgetContainer& p_root, const std::string& p_name, Vector2& p_data, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
	static void DrawVec3(WidgetContainer& p_root, const std::string& p_name, Vector3& p_data, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
	static void DrawVec4(WidgetContainer& p_root, const std::string& p_name, Vector4& p_data, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
	static void DrawQuat(WidgetContainer& p_root, const std::string& p_name, Quaternion& p_data, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
	static void DrawString(WidgetContainer& p_root, const std::string& p_name, std::string& p_data);
	static void DrawColor(WidgetContainer& p_root, const std::string& p_name, Color3& p_color, bool p_hasAlpha = false);
	static void DrawColor(WidgetContainer& p_root, const std::string& p_name, Color4& p_color, bool p_hasAlpha = false);
	static Text& DrawMaterial(WidgetContainer& p_root, const std::string& p_name, Material*& p_data, Event<>* p_updateNotifier);
	static Text& DrawShader(WidgetContainer& p_root, const std::string& p_name, CShader*& p_data, Event<>* p_updateNotifier);
	static Image& DrawTexture(WidgetContainer& p_root, const std::string& p_name, Texture* p_data, std::function<void(std::string, Texture*)> p_setTextureValue);
	static Image& DrawTexture(WidgetContainer& p_root, const std::string& p_name, Texture* p_data, Event<>* p_updateNotifier = nullptr);

	template <typename T>
	static void DrawScalar(WidgetContainer& p_root, const std::string& p_name, std::function<T(void)> p_gatherer, std::function<void(T)> p_provider, float p_step = 1.f, T p_min = std::numeric_limits<T>::min(), T p_max = std::numeric_limits<T>::max());
	static void DrawBoolean(WidgetContainer& p_root, const std::string& p_name, std::function<bool(void)> p_gatherer, std::function<void(bool)> p_provider);
	static void DrawVec2(WidgetContainer& p_root, const std::string& p_name, std::function<Vector2(void)> p_gatherer, std::function<void(Vector2)> p_provider, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
	static void DrawVec3(WidgetContainer& p_root, const std::string& p_name, std::function<Vector3(void)> p_gatherer, std::function<void(Vector3)> p_provider, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
	static void DrawVec4(WidgetContainer& p_root, const std::string& p_name, std::function<Vector4(void)> p_gatherer, std::function<void(Vector4)> p_provider, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
	static void DrawQuat(WidgetContainer& p_root, const std::string& p_name, std::function<Quaternion(void)> p_gatherer, std::function<void(Quaternion)> p_provider, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
	static void DrawString(WidgetContainer& p_root, const std::string& p_name, std::function<std::string(void)> p_gatherer, std::function<void(std::string)> p_provider);
	static void DrawColor(WidgetContainer& p_root, const std::string& p_name, std::function<Color3(void)> p_gatherer, std::function<void(Color3)> p_provider, bool p_hasAlpha = false);
	static void DrawColor(WidgetContainer& p_root, const std::string& p_name, std::function<Color4(void)> p_gatherer, std::function<void(Color4)> p_provider, bool p_hasAlpha = false);

	//static void DrawCombox(WidgetContainer& p_root, const std::string& p_name, DepthFunc& p_depthTest);
	//static void DrawCombox(WidgetContainer& p_root, const std::string& p_name, BlendParam& p_blendParam);
	//static void DrawCombox(WidgetContainer& p_root, const std::string& p_name, BlendFunc& p_blendFunc);
	//static void DrawCombox(WidgetContainer& p_root, const std::string& p_name, CullFace& p_cullFace);
	//static void DrawCombox(WidgetContainer& p_root, const std::string& p_name, FrontFace& p_frontFace);

	template <typename T>
	static std::string GetFormat();

	template <typename T>
	static ImGuiDataType_ GetDataType();

private:
	static Texture* __EMPTY_TEXTURE;

};

#include "GUIDrawer.inl"