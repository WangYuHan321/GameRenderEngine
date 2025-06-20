#include "RenderThreadSys.h"
RenderThreadSys::RenderThreadSys()
#ifdef WINDOWS_PLATFORM
	:WinThread()
#endif
{
}

RenderThreadSys::~RenderThreadSys()
{
}


void RenderThreadSys::Run()
{
	while (!IsStopTrigger())
	{
	}
}

string RenderThreadSys::GetThreadName()const
{
	return "RenderThreadSys";
}