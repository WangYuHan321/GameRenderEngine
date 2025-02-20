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
		TS_START,//��ʼ
		TS_SUSPEND,//����ָ���߳�
		TS_STOP,//ֹͣ
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


