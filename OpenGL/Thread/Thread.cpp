#include "Thread.h"
BaseThread::BaseThread() :
	m_hThread(nullptr),
	m_priority(Priority::Normal),
	m_stackSize(0)
{
}

BaseThread::~BaseThread()
{
}

void BaseThread::SetPriority(Priority p)
{
	m_priority = p;
}

BaseThread::Priority BaseThread::GetPriority() const
{
	return m_priority;
}

void BaseThread::Run() 
{
}

void BaseThread::Start()
{
}

void BaseThread::Suspend()
{
}

void BaseThread::Sleep(int millSecond)
{
}

bool BaseThread::IsRuning()
{
	return false;
}

void BaseThread::Stop()
{
}

bool BaseThread::IsStopTrigger()
{
	return m_event.IsTrigger();
}

string BaseThread::GetThreadName() const
{
	return "VSThread";
}