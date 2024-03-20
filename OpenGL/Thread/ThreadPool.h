#pragma once

#include<list>
#include<mutex>
#include<queue>
#include<thread>
#include "../Util/Singleton.h"

class IRunable;

class ThreadPool : public CSingleton<ThreadPool>
{
private:
	std::list<std::thread> m_pool;
	std::queue<std::unique_ptr<IRunable>> m_tasks;

	std::mutex m_globalLock;
	std::condition_variable m_monitor;

	bool m_active;
	unsigned int m_poolSize;

public:
	explicit ThreadPool();
	~ThreadPool();
	unsigned int GetPoolSize() const ;
	bool IsActive();

	void Init();
	void AddTask(std::unique_ptr<IRunable> task);
	void ShutDown();
	void PollTask();

};

