#pragma once
#include<iostream>
#include<functional>
#include "../Event/Event.h"

class Scene;
class SceneNode;

class SceneManager
{
public:
	SceneManager(const std::string& p_sceneRootFolder = "");
	~SceneManager();

	void Update();
	void LoadEmptyScene();
	void UnloadCurScene();

public:
	Event<> SceneLoadEvent;
	Event<> SceneUnloadEvent;
	Event<const std::string&> CurrentSceneSourcePathChangedEvent;

private:
	const std::string m_sceneRootFolder;
	Scene* m_curScene;

	bool m_curSceneLoadedFromPath;
	std::string m_curSceneSourcePath = "";

	std::function<void()> m_delayedLoadCall;
};

