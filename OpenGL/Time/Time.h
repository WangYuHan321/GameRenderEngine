#pragma once

#include<GLFW/glfw3.h>

class Time
{

private:
	float m_currentFrameTime;
	float m_deltaTime;
	float m_lastFrameTime;

public:

	Time();
	~Time();

	void Update();
	float GetDeltaTime() { return m_deltaTime; }

};

