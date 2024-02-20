#pragma once

#include <memory>

#include "../../UI/UIManager.h"
#include "../../Window/Window.h"
//#include "../../Render/Renderer.h"
#include "../../Camera/Camera.h"
#include "../../Time/Time.h"
#include "../../Log/DumpFileManager.h"
#include "../../Window/Context/Device.h"
#include "../../Render/Context/Driver.h"
#include "../../Scene/Scene.h"
#include "../../Render/BaseRenderer.h"
#include "../../Render/ForwardRenderer.h"
#include "../../Scene/SceneManager.h"
#include "../../Editor/Core/EditorResource.h"
#include "../../Window/Input/InputManager.h"
#include "../../Render/Resource/ModelManager.h"
#include "../../Render/Resource/ShaderManager.h"
#include "../../Render/Resource/TextureManager.h"

class Context
{
public:


	Context(const string& p_projectPath, const string& p_projectName);

	~Context();

	std::unique_ptr<Window> m_window;
	std::unique_ptr<Driver> m_dirve;
	std::unique_ptr<Device> m_device;
	std::unique_ptr<UIManager> m_uiMgr;
	std::unique_ptr<BaseRenderer> m_renderer;
	std::unique_ptr<SceneManager> m_sceneMgr;
	std::unique_ptr<InputManager> m_inputMgr;

	std::unique_ptr<DumpFileManager> m_dumpFileMgr;
	std::unique_ptr<EditorResource> m_editorResource;

	ModelManager modelMgr;
	ShaderManager shaderMgr;
	TextureManager textureMgr;
	
private:
	
	const std::string m_engineAssetsPath;

};

