#include "Scene.h"
#include "SceneNode.h"
#include "SceneManager.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CCamera.h"
#include "../../Core/ECS/Components/CDirectionalLight.h"

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

void SceneManager::LoadEmptyLightedScene()
{
	LoadEmptyScene();

	auto directionLight = m_curScene->CreateActor("Directional Light");
	directionLight->AddComponent<CDirectionalLight>().SetIntensity(0.75f);
	directionLight->m_transform.SetLocalPosition(Vector3(0.0f, 10.0f, 0.0f));
	directionLight->m_transform.SetLocalRotation(Quaternion(120.0f, -40.0f, 0.0f, 1.0f));

	auto camera = m_curScene->CreateActor("Main Camera");
	camera->AddComponent<CCamera>();
	camera->m_transform.SetLocalPosition(Vector3(0.0f, 3.0f, 8.0f));
	camera->m_transform.SetLocalRotation(Quaternion(20.0f, 180.0f, 0.0f, 1.0f));
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

void SceneManager::SetActiveScene(Scene* p_scene)
{
	m_curScene = p_scene;
}