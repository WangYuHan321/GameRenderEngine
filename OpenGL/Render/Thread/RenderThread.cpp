#include "RenderThread.h"
#include "RenderCommand.h"

RenderThreadBuffer::RenderThreadBuffer()
{
}

RenderThreadBuffer::~RenderThreadBuffer()
{
}

void RenderThreadBuffer::Execute()
{
	for (int i = 0; i < m_CommandList.size(); i++)
		m_CommandList[i]->Execute();
}

RenderThread::RenderThread()
#ifdef WINDOWS_PLATFORM
	:WinThread(),
#endif
	m_pRenderBuffer(nullptr)
{
}

RenderThread::~RenderThread()
{
}


void RenderThread::Run()
{
	while (!IsStopTrigger())
	{
		m_pRenderBuffer->Execute();
	}
}

bool RenderThread::IsReady()
{
	return m_pRenderBuffer == nullptr;
}

string RenderThread::GetThreadName()const
{
	return "RenderThread";
}