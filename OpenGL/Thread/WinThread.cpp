#include "WinThread.h"
WinThread::WinThread():
	BaseThread()
{
	m_hThread = ::CreateThread(0, m_stackSize, ThreadProc, this, CREATE_SUSPENDED, NULL);
}

WinThread::~WinThread()
{
	TerminateThread(m_hThread, 0);
}

DWORD THREAD_CALLBACK WinThread::ThreadProc(void* t)
{
	BaseThread* pBaseThread = (BaseThread*)t;
	pBaseThread->Run();
	return 0;
}

void WinThread::Start()
{
	if (m_tsState == TS_SUSPEND)
	{
		ResumeThread((HANDLE)m_hThread);
		m_tsState = TS_START;
	}
}

void WinThread::Suspend()
{
	if (m_tsState == TS_START)
	{
		SuspendThread((HANDLE)m_hThread);
		m_tsState = TS_SUSPEND;
	}
}

void WinThread::Run()
{
}

bool WinThread::IsRuning()
{
	if (m_hThread != nullptr)
	{
		DWORD exitCode = 0;
		if (GetExitCodeThread(m_hThread, &exitCode))
		{
			if (STILL_ACTIVE == exitCode)
			{
				return true;
			}
		}
	}
}

void WinThread::Stop()
{
	if (m_tsState == TS_START)
	{
		m_event.Trigger();
		m_tsState = TS_STOP;
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = nullptr;
	}
}

void WinThread::Sleep(int millSecond)
{
	::Sleep(millSecond);
}

void WinThread::SetPriority(Priority p)
{
	BaseThread::SetPriority(p);

	int nPrority = THREAD_PRIORITY_NORMAL;

	if (p == Low)
		nPrority = THREAD_PRIORITY_BELOW_NORMAL;
	else if(p == Normal)
		nPrority = THREAD_PRIORITY_NORMAL;
	else if (p == High)
		nPrority = THREAD_PRIORITY_ABOVE_NORMAL;

	::SetThreadPriority(m_hThread, nPrority);
}
