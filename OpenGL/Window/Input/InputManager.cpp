#include "InputManager.h"
#include "../Window.h"

InputManager::InputManager()
{
	//处理事件
	m_keyDownListener = Window::getInstance()->KeyDownEvent.
		AddListenerID(std::bind(&InputManager::OnKeyDown, this, std::placeholders::_1));

	m_keyReleaseListener = Window::getInstance()->KeyReleaseEvent.
		AddListenerID(std::bind(&InputManager::OnKeyRelease, this, std::placeholders::_1));

	m_mouseButtonDownListener = Window::getInstance()->MouseButtonDownEvent.
		AddListenerID(std::bind(&InputManager::OnMouseDown, this, std::placeholders::_1));
	
	m_mouseButtonReleaseListener = Window::getInstance()->MouseButtonReleaseEvent.
		AddListenerID(std::bind(&InputManager::OnMouseRelease, this, std::placeholders::_1));
	
}

void InputManager::OnStartUp()
{
}

void InputManager::OnEnd()
{

}

InputManager::~InputManager()
{
	/*Window::getInstance()->KeyReleaseEvent.RemoveListenerID(m_keyReleaseListener);
	Window::getInstance()->KeyReleaseEvent.RemoveListenerID(m_keyReleaseListener);
	Window::getInstance()->KeyReleaseEvent.RemoveListenerID(m_keyReleaseListener);*/
}

void InputManager::OnKeyRelease(uint32 key_btn)
{
	m_keyEvents[static_cast<EKey>(key_btn)] = EKeyState::KEY_UP;
}

void InputManager::OnKeyDown(uint32 key_btn)
{
	m_keyEvents[static_cast<EKey>(key_btn)] = EKeyState::KEY_DOWN;
}

void InputManager::OnMouseRelease(uint32 mouse_btn)
{
	m_mouseState[static_cast<EMouseButton>(mouse_btn)] = EMouseButtonState::MOUSE_UP;
}

void InputManager::OnMouseDown(uint32 mouse_btn)
{
	m_mouseState[static_cast<EMouseButton>(mouse_btn)] = EMouseButtonState::MOUSE_DOWN;
}

bool InputManager::IsKeyPressed(EKey p_key)
{
	return (m_keyEvents.find(p_key) != m_keyEvents.end()) ? (m_keyEvents[p_key] == EKeyState::KEY_DOWN) : false;
}

std::pair<double, double> InputManager::GetMousePosition() const
{
	std::pair<double, double> result;
	glfwGetCursorPos(Window::getInstance()->GetWindow(), &result.first, &result.second);
	return result;
}

bool InputManager::IsKeyReleased(EKey p_key)
{
	return (m_keyEvents.find(p_key) != m_keyEvents.end()) ? (m_keyEvents[p_key] == EKeyState::KEY_UP) : false;
}

bool InputManager::IsMouseButtonPressed(EMouseButton mouse_btn)
{
	return (m_mouseState.find(mouse_btn) != m_mouseState.end()) ? (m_mouseState[mouse_btn] == EMouseButtonState::MOUSE_DOWN) : false;
}

bool InputManager::IsMouseButtonReleased(EMouseButton mouse_btn)
{
	return (m_mouseState.find(mouse_btn) != m_mouseState.end()) ? (m_mouseState[mouse_btn] == EMouseButtonState::MOUSE_UP) : false;
}

void InputManager::ClearEvents()
{
	for (auto key = m_keyEvents.begin(); key != m_keyEvents.end();)
	{
		if (key->second == EKeyState::KEY_UP)
		{
			m_keyEvents.erase(key++);
		}
		else
			++key;
	}
	
	for (auto mouse = m_mouseState.begin(); mouse != m_mouseState.end();)
	{
		if (mouse->second == EMouseButtonState::MOUSE_UP)
		{
			m_mouseState.erase(mouse++);
		}
		else
			++mouse;
	}

}
