#include "Device.h"
Device::Device()
{	
	int initCode = glfwInit();

	if (initCode == GLFW_FALSE)
	{
		Log("glfwInit error !!!\n");
		glfwTerminate();
	}
	else
	{
		CreateCursor();
	}
	BindErrorwCallback();
}

Device::~Device()
{
	DestroyCursors();
	glfwTerminate();
}

void Device::CreateCursor()
{
	m_cursor[CursorShape::ARROW] = glfwCreateStandardCursor(static_cast<int>(CursorShape::ARROW));
	m_cursor[CursorShape::IBEAM] = glfwCreateStandardCursor(static_cast<int>(CursorShape::IBEAM));
	m_cursor[CursorShape::CROSSHAIR] = glfwCreateStandardCursor(static_cast<int>(CursorShape::CROSSHAIR));
	m_cursor[CursorShape::HAND] = glfwCreateStandardCursor(static_cast<int>(CursorShape::HAND));
	m_cursor[CursorShape::HRESIZE] = glfwCreateStandardCursor(static_cast<int>(CursorShape::HRESIZE));
	m_cursor[CursorShape::VRESIZE] = glfwCreateStandardCursor(static_cast<int>(CursorShape::VRESIZE));
}

void Device::BindErrorwCallback()
{
	auto errorCallback = [](int p_code, const char* p_desc)
	{
		Device::getInstance()->ErrorEvent.Invoke(static_cast<DeviceError>(p_code), p_desc);
	};
	glfwSetErrorCallback(errorCallback);
}

void Device::DestroyCursors()
{
	glfwDestroyCursor(m_cursor[CursorShape::ARROW]);
	glfwDestroyCursor(m_cursor[CursorShape::IBEAM]);
	glfwDestroyCursor(m_cursor[CursorShape::CROSSHAIR]);
	glfwDestroyCursor(m_cursor[CursorShape::HAND]);
	glfwDestroyCursor(m_cursor[CursorShape::HRESIZE]);
	glfwDestroyCursor(m_cursor[CursorShape::VRESIZE]);
}

void Device::PollEvents() const
{
	glfwPollEvents();
}

GLFWcursor* Device::GetCursorInstance(CursorShape shape)
{
	return m_cursor.at(shape);
}