#include "GlobalContext.h"

GlobalContext::GlobalContext():
	m_engineAssetsPath("Data\\Engine\\")
{


	m_device = Device::getInstance();
	Log("Device inited success!!!\n");

	m_window = Window::getInstance();
	Log("Window inited success!!!\n");
	
	m_dirve = Driver::getInstance();
	Log("Device inited success!!!\n");
	
	m_timeMgr = TimeManager::getInstance();
	Log("Time inited success!!!\n");
	
	m_inputMgr = InputManager::getInstance();
	Log("Input inited success!!!\n");
	
	m_resourceMgr = ResourceManager::getInstance();
	m_resourceMgr->SetAssetPath(m_engineAssetsPath);
	m_resourceMgr->OnStartUp();
	Log("Resource inited success!!!\n");

	m_dumpFileMgr = DumpFileManager::getInstance();
	Log("Dump inited success!!!\n");
	//m_dumpFileMgr->OnStartUp();

	m_renderer = new Renderer();
	m_Camera = new FlyCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	m_renderer->SetRenderSize(m_window->GetWindowSize().x, m_window->GetWindowSize().y);
}

GlobalContext::~GlobalContext()
{
	if (m_Camera)
		delete m_Camera;
	
	if (m_renderer)
		delete m_renderer;
}