#pragma once

#include "./Util.h"
#include "Thread.h"

class WinThread : public BaseThread
{
public:
	WinThread();
	virtual ~WinThread();

	void Start();
	void Suspend();

	void Run();
	bool IsRuning();
	void Stop();
	void Sleep(int millSecond);
	void SetPriority(Priority p);

private:
	static DWORD THREAD_CALLBACK ThreadProc(void* t);

};


