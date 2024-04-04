#include "Scene.h"
#include "SceneNode.h"
#include "SceneManager.h"
#include "../../File/XmlManager.h"
#include "../../Core/ECS/Actor.h"
#include "../../Global/ServiceLocator.h"
#include "../../Core/ECS/Components/CCamera.h"
#include "../../Core/ECS/Components/CAmbientSphereLight.h"
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

#ifndef USE_NO_EDITOR

void SceneManager::LoadEmptyLightedScene()
{
	LoadEmptyScene();

	auto directionLight = m_curScene->CreateActor(GLOBALSERVICE(XmlManager).GetLanguage(DIRECTIONLIGHT_TEXT));
	directionLight->AddComponent<CDirectionalLight>().SetIntensity(0.15f);
	directionLight->GetComponent<CDirectionalLight>()->SetColor(Color3(0.03, 0.05, 0.03));
	directionLight->m_transform.SetLocalPosition(Vector3(0.0f, 10.0f, 0.0f));
	directionLight->m_transform.SetLocalRotation(Quaternion(Vector3(120.0f, -40.0f, 0.0f)));

	auto ambientLight = m_curScene->CreateActor(GLOBALSERVICE(XmlManager).GetLanguage(AMBIENTLIGHT_TEXT));
	ambientLight->AddComponent<CAmbientSphereLight>().SetRadius(10000.0f);
	ambientLight->GetComponent<CAmbientSphereLight>()->SetColor(Color3(0.1, 0.1, 0.1));

	auto camera = m_curScene->CreateActor(GLOBALSERVICE(XmlManager).GetLanguage(MainCAMERA_TEXT));
	camera->AddComponent<CCamera>();
	camera->m_transform.SetLocalPosition(Vector3(0.0f, 3.0f, 8.0f));
	camera->m_transform.SetLocalRotation(Quaternion(Vector3(20.0f, 180.0f, 0.0f)));
}























#endif
