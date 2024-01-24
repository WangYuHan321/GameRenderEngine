#pragma once

#include <memory>

#include "../../UI/UIManager.h"
#include "../../Window/Window.h"
#include "../../Render/Renderer.h"
#include "../../Camera/Camera.h"
#include "../../Time/TimeManager.h"
#include "../../Log/DumpFileManager.h"
#include "../../Window/Context/Device.h"
#include "../../Render/Context/Driver.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneManager.h"
#include "../../Window/Input/InputManager.h"
#include "../../Render/Resource/ResourceManager.h"

class Context
{
public:


	Context(const string& p_projectPath, const string& p_projectName);

	~Context();


	std::shared_ptr<Window> m_window;
	std::shared_ptr<Device> m_device;
	std::shared_ptr<Driver> m_dirve;
	std::shared_ptr<UIManager> m_uiMgr;
	std::shared_ptr<TimeManager> m_timeMgr;
	std::shared_ptr<InputManager> m_inputMgr;
	std::shared_ptr<ResourceManager> m_resourceMgr;
	std::shared_ptr<DumpFileManager> m_dumpFileMgr;

	std::shared_ptr<SceneManager> m_sceneMgr;

	Camera* m_Camera;
	Renderer* m_renderer;

private:
	
	const std::string m_engineAssetsPath;

};

