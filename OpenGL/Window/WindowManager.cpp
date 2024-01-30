#include "WindowManager.h"

void WindowManager::RegisterWindow(GLFWwindow* p_glfwWindow, Window* p_window)
{
	if (__WINDOWS_MAP.find(p_glfwWindow) == __WINDOWS_MAP.end())
	{
		__WINDOWS_MAP.emplace(p_glfwWindow, p_window);
	}
}

void WindowManager::UnregisterWindow(GLFWwindow* p_glfwWindow)
{
	if (__WINDOWS_MAP.find(p_glfwWindow) != __WINDOWS_MAP.end())
	{
		__WINDOWS_MAP.erase(p_glfwWindow);
	}
}

Window* WindowManager::GetWindow(GLFWwindow* glfwWindow)
{
	if (__WINDOWS_MAP.find(glfwWindow) != __WINDOWS_MAP.end())
		return __WINDOWS_MAP[glfwWindow];
	return nullptr;
}
