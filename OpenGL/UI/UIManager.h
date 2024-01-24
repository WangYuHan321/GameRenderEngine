#pragma once

//form OverLoad
#include <string>
#include "../Util/Singleton.h"
#include "../ThirdLib/ImGui/imgui.h"
#include "../ThirdLib/ImGui/imgui_internal.h"
#include "../ThirdLib/ImGui/imgui_impl_glfw.h"
#include "../ThirdLib/ImGui/imgui_impl_opengl3.h"

class GLFWwindow;
class Canvas;
class Hierarchy;

class UIManager : public CSingleton<UIManager>
{
public:
	UIManager();
	~UIManager();

	void OnInit(GLFWwindow* p_window, const std::string& p_glslVersion = "#version 150");
	void OnEnd();
	void Render();

private:
	Canvas* m_currentCanvas = nullptr;
	Hierarchy* m_testPanel;
};

