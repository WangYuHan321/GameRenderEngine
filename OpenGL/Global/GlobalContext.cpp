#include "GlobalContext.h"
#include <memory>

GlobalContext::GlobalContext() :
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

	m_timeMgr = std::make_unique<Time>();
	LOG_INFO("Time inited success!!!\n");

	m_inputMgr = std::make_unique<InputManager>(*m_window);
	LOG_INFO("Input inited success!!!\n");


	m_dumpFileMgr = std::make_unique<DumpFileManager>();
	LOG_INFO("Dump inited success!!!\n");
	//m_dumpFileMgr->OnStartUp();

	m_sceneMgr = SceneManager::getInstance();
	LOG_INFO("scene inited success!!!\n");

	m_resourceMgr = ResourceManager::getInstance();
	m_resourceMgr->SetAssetPath(m_engineAssetsPath);
	m_resourceMgr->SetContext(this);
	m_resourceMgr->OnStartUp();
	LOG_INFO("Resource inited success!!!\n");

	m_renderer = std::make_unique<Renderer>(*this);
	LOG("new  Render");
	//m_Camera = std::make_unique<Camera>(new Camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	//LOG("new FlyCamera");
	m_renderer->SetRenderSize(m_window->GetWindowSize().x, m_window->GetWindowSize().y);
}

GlobalContext::~GlobalContext()
{
	m_uiMgr->OnEnd();
	m_window->OnEnd();
	m_device->OnEnd();
}