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
	Time clock;

	while (IsRunning())
	{
		m_editor.PreUpdate();
		m_editor.Update(clock.GetDeltaTime());
		m_editor.PostUpdate();

		clock.Update();
	}
}

bool Application::IsRunning() const
{
	return !m_context.m_window->ShouldClose();
}