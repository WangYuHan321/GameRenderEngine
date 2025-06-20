#pragma once
#include "../../Util/common.h"
#include "../../Thread/Thread.h"

#ifdef WINDOWS_PLATFORM
	#include "../../Thread/WinThread.h"
#endif
class RenderThreadSys : 
#ifdef WINDOWS_PLATFORM
	public WinThread
#else
	public BaseThread
#endif
{
public:
	RenderThreadSys();
	virtual ~RenderThreadSys();

	void Run();

protected:
	virtual string GetThreadName()const;
};

