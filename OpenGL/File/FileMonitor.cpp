#include "FileMonitor.h"
#include <filesystem>
#include <windows.h>
#include <locale>
#include <codecvt>
#include "ResourceChangeHandler.h"
#include "LuaFileChangeHandler.h"
#include "ShaderFileChangeHandler.h"

FileMonitor::FileMonitor()
{
	m_pArg = new FileChangeArgs();
	LuaFileChangeHandler* pHandler1 = new LuaFileChangeHandler();
	ShaderFileChangeHandler* pHandler2 = new ShaderFileChangeHandler();
	ResgisterHandler(pHandler1);
	ResgisterHandler(pHandler2);
}

FileMonitor::~FileMonitor()
{
	for (auto it : m_pOwnders)
		delete it;
	delete m_pArg;
}

void FileMonitor::SetDirectory(std::string directoryName)
{
	m_directoryStr = directoryName;
}

std::wstring to_wide_string(std::string input)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(input);
}


std::string stows(std::wstring ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char* _Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

FileOperate::Type GetOperatorTypeByAction(DWORD dwType)
{
	switch (dwType)
	{
	case 0x00000001:
		return FileOperate::Added;
		break;

	case 0x00000002:
		return FileOperate::Removed;
		break;

	case 0x00000003:
		return FileOperate::Modified;
		break;
	}

	return FileOperate::None;
}

void FileMonitor::Run()
{
#ifdef WINDOWS_PLATFORM

	HRESULT hr = S_OK;
	OVERLAPPED overlapped = { 0 };
	std::wstring str = to_wide_string(m_directoryStr);

	HANDLE hDir = ::CreateFile((LPCSTR)str.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);

	if (INVALID_HANDLE_VALUE == hDir)
	{
		LOG_ERROR("current thread 0x" + std::to_string(GetCurrentThreadId()) + " error code " + std::to_string(GetLastError())); return;
	}

	while (hr == S_OK)
	{
		DWORD dwBytesReturned = 0;
		DWORD dwBytesTransferred = 0;
		FILE_NOTIFY_INFORMATION* pInfo = (FILE_NOTIFY_INFORMATION*)m_readBuffer;
		memset(m_readBuffer, 0, 1024);
		if (0 == ::ReadDirectoryChangesW(hDir, pInfo, 1024, TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
			&dwBytesReturned, &overlapped, NULL))
		{
			LOG_ERROR("current thread 0x" + std::to_string(GetCurrentThreadId()) + " error code " + std::to_string(GetLastError())); return;
		}

		if (0 == ::GetOverlappedResult(hDir, &overlapped,
			&dwBytesTransferred, TRUE))
		{
			LOG_ERROR("current thread 0x" + std::to_string(GetCurrentThreadId()) + " error code " + std::to_string(GetLastError())); return;
		}
		else
		{
			m_pArg->filePath = stows(pInfo->FileName);
			m_pArg->Operator = GetOperatorTypeByAction(pInfo->Action);
			this->NotifyHandler();
		}
	}

	CloseHandle(hDir);

#endif
}

void FileMonitor::ResgisterHandler(ResourceChangeHandler* other)
{
	m_pOwnders.push_back(other);
}

void FileMonitor::NotifyHandler()
{
	for (int i = 0; i < m_pOwnders.size(); i++)
	{
		m_pOwnders[i]->OnFileChanged(*m_pArg);
	}

}