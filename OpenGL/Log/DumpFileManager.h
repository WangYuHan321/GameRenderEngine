#pragma once

#include <windows.h>
#include <imagehlp.h>
#include "../Util/common.h"
#include "../Util/Singleton.h"

static LONG WINAPI MyUnhandledExceptionFilter(
    struct _EXCEPTION_POINTERS* ExceptionInfo
);
static void CreateMiniDump(EXCEPTION_POINTERS* pep);

static LONG WINAPI MyUnhandledExceptionFilter(
    struct _EXCEPTION_POINTERS* ExceptionInfo
)
{
    CreateMiniDump(ExceptionInfo);
    return EXCEPTION_EXECUTE_HANDLER;
}

static void CreateMiniDump(EXCEPTION_POINTERS* pep)
{
#ifdef WINDOWS_PLATFORM

    // Open the file
    typedef BOOL(*PDUMPFN)(
        HANDLE hProcess,
        DWORD ProcessId,
        HANDLE hFile,
        MINIDUMP_TYPE DumpType,
        PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
        PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
        PMINIDUMP_CALLBACK_INFORMATION CallbackParam
        );


    HANDLE hFile = CreateFileA("C://dump.dmp", GENERIC_READ | GENERIC_WRITE,
        0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    HMODULE h = ::LoadLibraryA("DbgHelp.dll");
    PDUMPFN pFn = (PDUMPFN)GetProcAddress(h, "SetUnhandledExceptionFilter");

    if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
    {
        // Create the minidump

        MINIDUMP_EXCEPTION_INFORMATION mdei;

        mdei.ThreadId = GetCurrentThreadId();
        mdei.ExceptionPointers = pep;
        mdei.ClientPointers = TRUE;

        MINIDUMP_TYPE mdt = MiniDumpNormal;

        BOOL rv = (*pFn)(GetCurrentProcess(), GetCurrentProcessId(),
            hFile, mdt, (pep != 0) ? &mdei : 0, 0, 0);

        // Close the file

        CloseHandle(hFile);

    }
#elif
    return;
#endif
}

class DumpFileManager 
{
private:

    BOOL PreventSetUnhandledExceptionFilter()
    {
#ifdef WINDOWS_PLATFORM
        DWORD dwOrgEntryAddr = 0;
        HMODULE hKernel32 = NULL;
        void* pOrgEntry = NULL;
        unsigned char newJump[100] = { 0 };
        void* pNewFunc = NULL;
        DWORD dwNewEntryAddr = 0;
        DWORD dwRelativeAddr = 0;
        SIZE_T bytesWritten = 0;

        if (NULL == (hKernel32 = LoadLibrary(L"kernel32.dll")))
        {
            return FALSE;
        }

        if (NULL == (pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter")))
        {
            return FALSE;
        }
        dwOrgEntryAddr = (DWORD)pOrgEntry;
        dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far

        pNewFunc = &MyUnhandledExceptionFilter;
        dwNewEntryAddr = (DWORD)pNewFunc;
        dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;

        newJump[0] = 0xE9;  // JMP absolute
        memcpy(&newJump[1], &dwRelativeAddr, sizeof(pNewFunc));

        return WriteProcessMemory(GetCurrentProcess(), pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
#elif
        return;
#endif
    }
public:
    DumpFileManager()
    {
    }

    void OnStartUp()
    {
        PreventSetUnhandledExceptionFilter();
        SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
    }

    void OnEnd()
    {

    }

    ~DumpFileManager() {}
};

