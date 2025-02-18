#pragma once

#include "./Util.h"

class Thread
{
public:
	enum Priority
	{
		Low, 
		Normal,
		Heigh,
	};

	enum ThreadState
	{
		TS_START,
		TS_SUSPEND,
		TS_STOP,
	};

public:
	Thread();
	virtual ~Thread();

	void SetPriority(Priority p);




private:
	Priority m_priority;

protected:
	ThreadState m_tsState;
	TEvent m_event;

};


