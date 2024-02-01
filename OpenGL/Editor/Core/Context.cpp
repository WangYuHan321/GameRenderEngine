#include "Context.h"
#include "../../Render/ForwardRenderer.h"
#include <memory>

Context::Context(const string& p_projectPath, const string& p_projectName):
	m_engineAssetsPath("Data\\Engine\\")
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

	m_renderer = std::make_unique<ForwardRenderer>();
	LOG("new  Render");
	//m_Camera = std::make_unique<Camera>(new Camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	//LOG("new FlyCamera");
}

Context::~Context()
{

	m_uiMgr->OnEnd();
	m_window->OnEnd();
	m_device->OnEnd();
}