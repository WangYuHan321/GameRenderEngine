#include "Context.h"

Context::Context(const string& p_projectPath, const string& p_projectName):
	m_engineAssetsPath("Data\\Engine\\")
{
	m_device = Device::getInstance();
	m_device->OnInit();
	LOG_INFO("Device inited success!!!\n");

	m_window = Window::getInstance();
	m_window->OnInit();
	LOG_INFO("Window inited success!!!\n");

	m_dirve = Driver::getInstance();
	LOG_INFO("Drive inited success!!!\n");

	m_uiMgr = UIManager::getInstance();
	m_uiMgr->OnInit(m_window->GetWindow());
	LOG_INFO("UI inited success!!!\n");

	m_timeMgr = TimeManager::getInstance();
	LOG_INFO("Time inited success!!!\n");

	m_inputMgr = InputManager::getInstance();
	LOG_INFO("Input inited success!!!\n");

	m_resourceMgr = ResourceManager::getInstance();
	m_resourceMgr->SetAssetPath(m_engineAssetsPath);
	m_resourceMgr->OnStartUp();
	LOG_INFO("Resource inited success!!!\n");

	m_dumpFileMgr = DumpFileManager::getInstance();
	LOG_INFO("Dump inited success!!!\n");
	//m_dumpFileMgr->OnStartUp();

	m_sceneMgr = SceneManager::getInstance();
	LOG_INFO("scene inited success!!!\n");

	m_renderer = new Renderer();
	LOG("new  Render");
	m_Camera = new Camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	LOG("new FlyCamera");
	m_renderer->SetRenderSize(m_window->GetWindowSize().x, m_window->GetWindowSize().y);

	m_renderer->SetCamera(m_Camera);
}

Context::~Context()
{
	if (m_Camera)
		delete m_Camera;
	LOG("delete FlyCamera");

	if (m_renderer)
		delete m_renderer;

	LOG("delete Renderer");

	m_uiMgr->OnEnd();
	m_window->OnEnd();
	m_device->OnEnd();
}