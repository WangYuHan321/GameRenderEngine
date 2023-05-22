#pragma once
#include "../Event/Event.h"
#include "../Util/Singleton.h"
#include "../Util/Utils.h"

class Window : public CSingleton<Window>
{
public:
	Event<uint32> KeyDownEvent;
	Event<uint32> KeyReleaseEvent;
	Event<uint32> MouseButtonDownEvent;
	Event<uint32> MouseButtonReleaseEvent;
	Event<uint32, uint32> ReSizeWindowEvent;
	Event<uint32, uint32> FrameBufferEvent;
	Event<double, double> MousePosEvent;

	Event<> MinimizeEvent;
	Event<> MaximizeEvent;
	Event<> CloseEvent;

public:
	Window();
	~Window();

	void BindKeyCallback();
	void BindMouseCallback();
	void BindCloseCallback();
	void BindResizeCallback();
	void BindMousePosCallback();
	void BindFrameBufferCallback();
	void CreateGLFWWindow(uint32 width, uint32 height);

	void SwapBuffer();
	bool ShouldClose() const;
	void SetShouldClose(bool p_value) const;
	void OnResize(uint32 width, uint32 height);
	void SetCursorShape(CursorShape p_cursorShape);

	void OnEnd();
	void OnInit(uint32 width = 800, uint32 height = 600);

	GLFWwindow* GetWindow() { return m_glfwWindow; }
	glm::vec2 GetWindowSize() { return m_glfwWindowSize; }
	void SetWindowSize(glm::vec2 size);

private:
	GLFWwindow* m_glfwWindow;
	CursorShape m_cursorShape;
	glm::vec2 m_glfwWindowSize;
};

