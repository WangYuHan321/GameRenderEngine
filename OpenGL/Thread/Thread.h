#pragma once

#include "./Util.h"

class BaseThread
{
public:
	enum Priority
	{
		Low = 0, 
		Normal,
		High,
	};

	enum ThreadState
	{
		TS_START,//开始
		TS_SUSPEND,//挂起指定线程
		TS_STOP,//停止
	};

public:
	BaseThread();
	virtual ~BaseThread();

	virtual void Start();
	virtual void Stop();
	virtual void Suspend();
	virtual void Sleep(int millSecond);
	virtual void Run();
	virtual bool IsRuning();
	virtual void SetPriority(Priority p);


	bool IsStopTrigger();
	Priority GetPriority() const;

protected:
	virtual string GetThreadName()const ;
private:
	Priority m_priority;

protected:
	ThreadState m_tsState;
	TEvent m_event;
	void* m_hThread;

	int m_stackSize;
};


