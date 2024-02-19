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

class UIManager
{
public:
	UIManager();
	~UIManager();

	void OnInit(GLFWwindow* p_window, const std::string& p_glslVersion = "#version 150");
	void OnEnd();
	void Render();

	void SetCanvas(Canvas& p_canvas);
	void EnableDocking(bool p_value);

private:
	bool m_dockingState;
	Canvas* m_currentCanvas = nullptr;
};

