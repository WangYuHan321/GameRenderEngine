#pragma once

#include "../Util/common.h"

#ifdef WINDOWS_PLATFORM
	
#include<Windows.h>

//在Window下只能保证 同一个进程下锁保护 其他进程访问则失效 临界区只用于用户态
class TCriticalSection
{
private:
	CRITICAL_SECTION m_criticalSection;
public:
	inline TCriticalSection()
	{
		InitializeCriticalSection(&m_criticalSection);
		SetCriticalSectionSpinCount(&m_criticalSection, 4000);
	}
	inline ~TCriticalSection()
	{
		DeleteCriticalSection(&m_criticalSection);
	}

	inline void Lock()
	{
		EnterCriticalSection(&m_criticalSection);
	}

	inline void Unlock()
	{
		LeaveCriticalSection(&m_criticalSection);
	}

};

class TMutex
{
private:
	void* m_pMutex;
public:
	inline TMutex()
	{
		m_pMutex = CreateMutex(NULL, false, NULL);
	}
	inline ~TMutex()
	{
		CloseHandle(m_pMutex);
	}

	inline void Lock()
	{
		WaitForSingleObject(m_pMutex, INFINITE);
	}

	inline void Unlock()
	{
		ReleaseMutex(m_pMutex);
	}

};

class TSemaphore
{
private:
	void* m_pMutex;
	int32 m_uiMaxCount;
public:
	inline TSemaphore(int32 uiCount, int maxCount):
		m_uiMaxCount(maxCount)
	{
		m_pMutex = CreateSemaphore(NULL, uiCount, maxCount, NULL);
	}
	inline ~TSemaphore()
	{
		CloseHandle(m_pMutex);
	}

	inline void Lock()
	{
		WaitForSingleObject(m_pMutex, INFINITE);
	}

	inline void Unlock(int32 uiCount)
	{
		ReleaseSemaphore(m_pMutex, uiCount, NULL);
	}
};

class TEvent
{
public:
	inline TEvent()
	{
		m_hEvent = CreateEvent(nullptr, false, false, nullptr);
	}

	inline ~TEvent()
	{
		CloseHandle(m_hEvent);
	}

	void Wait()
	{
		WaitForSingleObject(m_hEvent, INFINITE);
	}

	void TimeWait(int32 tw)
	{
		Reset();
		WaitForSingleObject(m_hEvent, tw);
	}

	void Set()
	{
		SetEvent(m_hEvent);
	}

	void Reset()
	{
		ResetEvent(m_hEvent);
	}

private:
	HANDLE m_hEvent;
};



#else


#include <pthread.h>

class TMutex
{
private:
	pthread_mutex_t m_pMutex;
public:
	inline TMutex()
	{
		pthread_mutexattr_t mAttr;
		memset(&mAttr, 0, sizeof(mAttr));
		pthread_mutexattr_init(&mAttr);

		pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&m_pMutex, &mAttr);
	}
	inline ~TMutex()
	{
		pthread_mutex_destroy(&m_pMutex);
	}

	inline void Lock()
	{
		pthread_mutex_lock(&m_pMutex);
	}

	inline void Unlock()
	{
		pthread_mutex_unlock(&m_pMutex);
	}

	class TSemaphore
	{
	private:
		set_t* m_pSem;
		char m_cMutexName[30];
	public:
		inline TSemaphore(const char* name) :
			m_uiMaxCount(maxCount)
		{
			memset(m_cMutexName, 0, sizeof(m_cMutexName));
			int min = strlen(name) > (sizeof(m_cMutexName) - 1) ? (sizeof(m_cMutexName) - 1) : strlen(name);
			strncpy(m_cMutexName, name, min);
			m_pSem = sem_open(name, O_CREAT, 0644, 1);
		}
		inline ~TSemaphore()
		{
			int ret = sem_close(m_pSem);
			if (0 != ret)
			{
				printf("sem_close error %d\n", ret);
			}
			sem_unlink(m_cMutexName);
		}

		inline void Lock()
		{
			int ret = sem_wait(m_pSem);
			if (ret != 0)
			{
				return false;
			}
			return true;
		}

		inline void Unlock(int32 uiCount)
		{
			int ret = sem_post(m_pSem);
			if (ret != 0)
			{
				return false;
			}
			return true;
		}
	};

	//class TEvent
	//{
	//public:
	//	inline TEvent()
	//	{
	//		m_hEvent = CreateEvent(nullptr, false, false, nullptr);
	//	}

	//	inline ~TEvent()
	//	{
	//		CloseHandle(m_hEvent);
	//	}

	//	void Wait()
	//	{
	//		WaitForSingleObject(m_hEvent, INFINITE);
	//	}

	//	void TimeWait(int32 tw)
	//	{
	//		Reset();
	//		WaitForSingleObject(m_hEvent, tw);
	//	}

	//	void Set()
	//	{
	//		SetEvent(m_hEvent);
	//	}

	//	void Reset()
	//	{
	//		ResetEvent(m_hEvent);
	//	}

	//private:
	//	CMutex m_Mutex;
	//	CCondition* m_pCond;
	//};

};


#endif

class TAutoMutex
{
public:

	TAutoMutex(TMutex* pMutex):
		m_pMutex(pMutex)
	{
		pMutex->Lock();
	}

	~TAutoMutex()
	{
		m_pMutex->Unlock();
	}

private:
	TMutex* m_pMutex;
};





