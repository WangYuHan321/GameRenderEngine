#pragma once

#include<GLFW/glfw3.h>
#include "../Util/Singleton.h"

class TimeManager : public CSingleton<TimeManager>
{

private:
	float m_currentFrameTime;
	float m_deltaTime;
	float m_lastFrameTime;

public:

	TimeManager();
	~TimeManager();

	void Update();
	float GetDeltaTime() { return m_deltaTime; }

};

