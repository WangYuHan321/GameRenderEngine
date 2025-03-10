#include "Window.h"
#include "GLFW/glfw3.h"
#include "Context/Device.h"
#include "WindowManager.h"


Window::Window(Device& p_device):
	m_device(p_device)
{
}

void Window::CreateGLFWWindow(uint32 width, uint32 height)
{
	glfwWindowHint(GLFW_RESIZABLE, true);
	glfwWindowHint(GLFW_DECORATED, true);
	glfwWindowHint(GLFW_FOCUSED, true);
	glfwWindowHint(GLFW_MAXIMIZED, false);
	//�Ƿ��ö�
	glfwWindowHint(GLFW_FLOATING, false);
	glfwWindowHint(GLFW_VISIBLE, true);
	glfwWindowHint(GLFW_AUTO_ICONIFY, true);
	glfwWindowHint(GLFW_REFRESH_RATE, 60);
	glfwWindowHint(GLFW_SAMPLES, 12);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	m_glfwWindowSize.x = width;
	m_glfwWindowSize.y = height;

	m_glfwWindow = glfwCreateWindow(m_glfwWindowSize.x, m_glfwWindowSize.y,
		"EasyEngine -- by WangYuHan", nullptr, nullptr);

	//#ifdef _DEBUG
	//	glEnable(GL_DEBUG_OUTPUT);
	//#endif 

	glfwMakeContextCurrent(m_glfwWindow);
	//glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	WindowManager::getInstance()->RegisterWindow(m_glfwWindow, this);
}

void Window::OnResize(uint32 width, uint32 height)
{
	m_glfwWindowSize.x = width;
	m_glfwWindowSize.y = height;
}

void Window::SwapBuffer()
{
	glfwSwapBuffers(m_glfwWindow);
}

void Window::OnInit(uint32 width, uint32 height)
{
	CreateGLFWWindow(width, height);
	BindKeyCallback();
	BindMouseCallback();
	BindCloseCallback();
	BindResizeCallback();
	BindMousePosCallback();
	BindFrameBufferCallback();
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "Status: Using GLFW %s\n", glfwGetVersionString());

	ReSizeWindowEvent.AddListenerID(std::bind(&Window::OnResize,
		this, std::placeholders::_1, std::placeholders::_2));
}

void Window::OnEnd()
{
	glfwDestroyWindow(m_glfwWindow);
}

void Window::SetCursorShape(CursorShape p_cursorShape)
{
	m_cursorShape = p_cursorShape;
	glfwSetCursor(m_glfwWindow,  m_device.GetCursorInstance(p_cursorShape));
}

void Window::BindKeyCallback()
{
	auto keyReleaseCallback = [](GLFWwindow* p_window, int p_key, int p_scanCode, int p_action, int p_modes)
	{
		if(p_action == GLFW_PRESS)
			WindowManager::getInstance()->GetWindow(p_window)->KeyDownEvent.Invoke(p_key);
		if (p_action == GLFW_RELEASE)
			WindowManager::getInstance()->GetWindow(p_window)->KeyReleaseEvent.Invoke(p_key);
	};
	glfwSetKeyCallback(GetWindow(), keyReleaseCallback);
}

void Window::BindMouseCallback()
{
	auto mouseCallback = [](GLFWwindow* p_window, int p_button, int p_action, int p_modes)
	{
		if (p_action == GLFW_PRESS)
			WindowManager::getInstance()->GetWindow(p_window)->MouseButtonDownEvent.Invoke(p_button);
		if (p_action == GLFW_RELEASE)
			WindowManager::getInstance()->GetWindow(p_window)->MouseButtonReleaseEvent.Invoke(p_button);

	};
	glfwSetMouseButtonCallback(GetWindow(), mouseCallback);
}

void Window::BindCloseCallback()
{
	auto closeCallback = [](GLFWwindow* p_window)
	{
		WindowManager::getInstance()->GetWindow(p_window)->CloseEvent.Invoke();
	};
	glfwSetWindowCloseCallback(GetWindow(), closeCallback);
}

void Window::BindResizeCallback()
{
	auto resizeCallback = [](GLFWwindow* p_window, int p_width, int p_height)
	{
		WindowManager::getInstance()->GetWindow(p_window)->ReSizeWindowEvent.Invoke(p_width, p_height);
	};
	glfwSetWindowSizeCallback(GetWindow(), resizeCallback);
}

void Window::BindMousePosCallback()
{
	auto mouseMoveCallback = [](GLFWwindow* p_widnow, double x, double y)
	{
		WindowManager::getInstance()->GetWindow(p_widnow)->MousePosEvent.Invoke(x, y);
	};
	glfwSetCursorPosCallback(GetWindow(), mouseMoveCallback);
}

void Window::BindFrameBufferCallback()
{
	auto frameBufferCallback = [](GLFWwindow* p_widnow, int32 x, int32 y)
	{
		WindowManager::getInstance()->GetWindow(p_widnow)->FrameBufferEvent.Invoke(x, y);
	};
	glfwSetFramebufferSizeCallback(GetWindow(), frameBufferCallback);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_glfwWindow);
}

void Window::SetWindowSize(glm::vec2 size)
{
	m_glfwWindowSize = size;
	glfwSetWindowSize(m_glfwWindow, m_glfwWindowSize.x, m_glfwWindowSize.y);
}

void Window::SetShouldClose(bool p_value) const
{
	return glfwSetWindowShouldClose(m_glfwWindow, p_value);
}

Window::~Window()
{
	CloseEvent.RemoveAllListeners();
	MousePosEvent.RemoveAllListeners();
	MinimizeEvent.RemoveAllListeners();
	MaximizeEvent.RemoveAllListeners();
	KeyDownEvent.RemoveAllListeners();
	KeyReleaseEvent.RemoveAllListeners();
	FrameBufferEvent.RemoveAllListeners();
	ReSizeWindowEvent.RemoveAllListeners();
	MouseButtonDownEvent.RemoveAllListeners();
	MouseButtonReleaseEvent.RemoveAllListeners();
}