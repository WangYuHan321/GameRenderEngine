#pragma once
#include <unordered_map>
#include "Window.h"
#include "../Util/Singleton.h"

class WindowManager : public CSingleton<WindowManager>
{
public:

	void RegisterWindow(GLFWwindow* p_glfwWindow, Window* p_window);
	void UnregisterWindow(GLFWwindow* p_glfwWindow);

	Window* GetWindow(GLFWwindow* glfwWindow);

private:
	std::unordered_map<GLFWwindow*, Window*> __WINDOWS_MAP;
};

