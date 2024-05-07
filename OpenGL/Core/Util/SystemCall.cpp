#include "SystemCall.h"
#include "../../File/ConfigManager.h"
#include "../../File/Path/PathParser.h"
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

void SystemCall::ShowSaveFileDialog(const std::string& p_path)
{

#ifdef WINDOWS_PLATFORM

	char lpStrFile[256] = {};
	char lpstrFileTitle[256] = { " Save File Scene " };

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = lpStrFile;
	ofn.nMaxFile = 256;
	ofn.lpstrTitle = lpstrFileTitle;
	ofn.nMaxFileTitle = 256;
	ofn.lpstrInitialDir = ConfigManager::getInstance()->GetProjectPath().data();
	ofn.lpstrFilter = "scene\0*.scene\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileNameA(&ofn) == TRUE) {
		printf("Selected file: %s\n", ofn.lpstrFile);
	}

#else
	LOG_INFO("No Implement ShowInExplore");
#endif

}

void SystemCall::ShowOpenFileDialog(const std::string& p_path)
{
#ifdef WINDOWS_PLATFORM

	char lpStrFile[256] = {};
	char lpstrFileTitle[256] = { " Load File Scene " };

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = lpStrFile;
	ofn.nMaxFile = 256;
	ofn.lpstrTitle = lpstrFileTitle;
	ofn.nMaxFileTitle = 256;
	ofn.lpstrInitialDir = ConfigManager::getInstance()->GetProjectPath().data();
	ofn.lpstrFilter = "scene\0*.scene\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn) == TRUE) {
		printf("Selected file: %s\n", ofn.lpstrFile);
}

#else
	LOG_INFO("No Implement ShowInExplore");
#endif
}