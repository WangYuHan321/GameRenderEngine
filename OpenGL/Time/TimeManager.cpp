#include "TimeManager.h"


TimeManager::TimeManager():
	m_currentFrameTime(0.0f),
	m_deltaTime(0.0f),
	m_lastFrameTime(0.0f)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	m_currentFrameTime = glfwGetTime();
	m_deltaTime = m_currentFrameTime - m_lastFrameTime;
	m_lastFrameTime = m_currentFrameTime;
}