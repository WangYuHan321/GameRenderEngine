#include "Application.h"

Application::Application(const std::string& p_projectPath, const std::string& p_projectName):
	m_context(p_projectPath, p_projectName),
	m_editor(m_context)
{

}
Application::~Application()
{

}

void Application::Run()
{
	m_editor.PreUpdate();
	m_editor.Update(TimeManager::getInstance()->GetDeltaTime());
	m_editor.PostUpdate();
	TimeManager::getInstance()->Update();
}