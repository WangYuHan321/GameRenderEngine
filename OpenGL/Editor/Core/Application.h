#pragma once

#include "Editor.h"

class Application
{

public:


	Application(const std::string& p_projectPath, const std::string& p_projectName);

	~Application();

	void Run();

	bool IsRunning() const;

private:
	Context m_context;
	Editor m_editor;

};

