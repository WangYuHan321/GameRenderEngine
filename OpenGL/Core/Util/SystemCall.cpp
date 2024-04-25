#include "SystemCall.h"
#ifdef WINDOWS_PLATFORM
#include <windows.h>
#else

#endif


void SystemCall::ShowInExplorer(const std::string& p_path)
{

#ifdef WINDOWS_PLATFORM

	ShellExecuteA(NULL, "open", p_path.c_str(), NULL, NULL, SW_SHOWNORMAL);

#else
	LOG_INFO("No Implement ShowInExplore");
#endif

}