#include "Scene.h"
#include "SceneNode.h"
#include "SceneManager.h"

SceneManager::SceneManager(const std::string& p_sceneRootFolder):
	m_sceneRootFolder(p_sceneRootFolder)
{
	LoadEmptyScene();
}

SceneManager::~SceneManager()
{
	UnloadCurScene();
}

void SceneManager::Update()
{
	if (m_delayedLoadCall)
	{
		m_delayedLoadCall();
		m_delayedLoadCall = 0;
	}
}

void SceneManager::LoadEmptyScene()
{
	UnloadCurScene();
	
	m_curScene = new Scene();

	SceneLoadEvent.Invoke();
}

void SceneManager::UnloadCurScene()
{
	if (m_curScene)
	{
		delete m_curScene;
		m_curScene = nullptr;
		SceneUnloadEvent.Invoke();
	}

}