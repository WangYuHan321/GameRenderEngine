#pragma once

#include "../UI/UIManager.h"
#include "../Window/Window.h"
#include "../Render/Renderer.h"
#include "../Camera/FlyCamera.h"
#include "../Time/Time.h"
#include "../Scene/SceneManager.h"
#include "../Log/DumpFileManager.h"
#include "../Window/Context/Device.h"
#include "../Render/Context/Driver.h"
#include "../Window/Input/InputManager.h"
#include "../Render/Resource/ResourceManager.h"

class GlobalContext
{
public:
	std::unique_ptr<Device> m_device;
	std::unique_ptr<Driver> m_dirve;
	std::unique_ptr<UIManager> m_uiMgr;
	std::unique_ptr<Time> m_timeMgr;
	std::shared_ptr<ResourceManager> m_resourceMgr;
	std::unique_ptr<DumpFileManager> m_dumpFileMgr;

	std::unique_ptr<Window> m_window;
	std::unique_ptr < Renderer> m_renderer;
	std::shared_ptr<SceneManager> m_sceneMgr;
	std::unique_ptr < InputManager> m_inputMgr;

	GlobalContext();
	~GlobalContext();

private:
	const std::string m_engineAssetsPath;
};

