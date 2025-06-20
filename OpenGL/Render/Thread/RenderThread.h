#pragma once
#include "../../Util/common.h"
#include "../../Thread/Thread.h"
class RenderCommand;

#ifdef WINDOWS_PLATFORM
	#include "../../Thread/WinThread.h"
#endif

class RenderThreadBuffer
{
public:
	RenderThreadBuffer();
	~RenderThreadBuffer();

	void Execute();

protected:
	std::vector<RenderCommand*> m_CommandList;
	TCriticalSection m_Lock;
};


class RenderThread : 
#ifdef WINDOWS_PLATFORM
	public WinThread
#else
	public BaseThread
#endif
{
public:
	RenderThread();
	virtual ~RenderThread();

	void Run();
	bool IsReady();

protected:
	virtual string GetThreadName()const;
	RenderThreadBuffer* m_pRenderBuffer;
};

