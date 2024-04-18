#include "Context.h"
#include "../../File/ConfigManager.h"
#include "../../Render/ForwardRenderer.h"
#include "../../Global/ServiceLocator.h"
#include <memory>

Context::Context(const string& p_projectPath, const string& p_projectName):
	m_engineAssetsPath(ConfigManager::getInstance()->GetEnginePath())
{
	m_device = std::make_unique<Device>();
	m_device->OnInit();
	LOG_INFO("Device inited success!!!\n");

	m_window = std::make_unique<Window>(*m_device);
	m_window->OnInit();
	LOG_INFO("Window inited success!!!\n");

	m_dirve = std::make_unique<Driver>();
	LOG_INFO("Drive inited success!!!\n");

	m_uiMgr = std::make_unique<UIManager>();
	m_uiMgr->OnInit(m_window->GetWindow());
	LOG_INFO("UI inited success!!!\n");

	m_inputMgr = std::make_unique<InputManager>(*m_window);
	LOG_INFO("Input inited success!!!\n");

	m_dumpFileMgr = std::make_unique<DumpFileManager>();
	LOG_INFO("Dump inited success!!!\n");
	//m_dumpFileMgr->OnStartUp();

	m_sceneMgr = std::make_unique<SceneManager>();
	LOG_INFO("scene inited success!!!\n");

	m_editorResource = std::make_unique<EditorResource>(ConfigManager::getInstance()->GetEditorPath());
	LOG_INFO("EditorResource inited success!!!\n");

	m_renderer = std::make_unique<ForwardRenderer>();
	LOG("new  Render");

	m_shadowMap = std::make_unique<ShadowMap>();
	LOG("new  ShadowMap");

	m_shapeDrawer = std::make_unique<ShapeDrawer>(*m_renderer);
	LOG("new  ShapeDrawer");

	ServiceLocator::getInstance()->Provide<ModelManager>(modelMgr);
	ServiceLocator::getInstance()->Provide<FontManager>(fontMgr);
	ServiceLocator::getInstance()->Provide<TextureManager>(textureMgr);
	ServiceLocator::getInstance()->Provide<ShaderManager>(shaderMgr);
	ServiceLocator::getInstance()->Provide<MaterialManager>(materialMgr);
	ServiceLocator::getInstance()->Provide<XmlManager>(xmlMgr);
	ServiceLocator::getInstance()->Provide<InputManager>(*m_inputMgr);
	ServiceLocator::getInstance()->Provide<Window>(*m_window);
	ServiceLocator::getInstance()->Provide<SceneManager>(*m_sceneMgr);
	ServiceLocator::getInstance()->Provide<ShadowMap>(*m_shadowMap);
	ServiceLocator::getInstance()->Provide<EditorResource>(*m_editorResource);

	fontMgr.Initialize();

	m_engineUBO = std::make_unique<UniformBuffer>(
		sizeof(Matrix4) +	//model
		sizeof(Matrix4) +	//view
		sizeof(Matrix4) +	//projection
		sizeof(Vector3) +	// view pos
		sizeof(float) +		//	time
		sizeof(Matrix4),	//user matrix

		0, 0,
		GL_DYNAMIC_DRAW
		);

	m_lightSSBO = std::make_unique<ShaderStorageBuffer>(GL_STREAM_DRAW);
	m_lightSSBO->Bind(0);
}

Context::~Context()
{
	m_uiMgr->OnEnd();
	m_window->OnEnd();
	m_device->OnEnd();
}