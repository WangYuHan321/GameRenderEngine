#include "Time.h"


Time::Time():
	m_currentFrameTime(0.0f),
	m_deltaTime(0.0f),
	m_lastFrameTime(0.0f)
{
}

Time::~Time()
{
}

void Time::Update()
{
	m_currentFrameTime = glfwGetTime();
	m_deltaTime = m_currentFrameTime - m_lastFrameTime;
	m_lastFrameTime = m_currentFrameTime;
}