#include "ThreadPool.h"
#include "../Log/Logger.h"
#include "Runable.h"

ThreadPool::ThreadPool()
{
	Init();
	LOG_INFO("Thread Pool Using "+ std::to_string(m_poolSize) + " threads");
}

ThreadPool::~ThreadPool()
{
	ShutDown();
}

unsigned int ThreadPool::GetPoolSize() const
{
	return m_poolSize;
}

bool ThreadPool::IsActive()
{
	return m_active;
}

void ThreadPool::Init()
{
	m_active = true;
	m_poolSize = std::thread::hardware_concurrency();
	m_poolSize = m_poolSize < 1 ? 1 : m_poolSize;

	for (unsigned i = 0; i < m_poolSize; i++)
	{
		std::thread t(&ThreadPool::PollTask, this);
		m_pool.push_back(std::move(t));
	}
}

void ThreadPool::AddTask(std::unique_ptr<IRunable> task)
{
	std::unique_lock<std::mutex> lock(m_globalLock);
	m_tasks.push(std::move(task));
	lock.unlock();
	m_monitor.notify_one();//只会通知线程池中一个
}

void ThreadPool::ShutDown()
{
	m_active = false;
	std::unique_lock<std::mutex> lock(m_globalLock);
	m_monitor.notify_all();
	lock.unlock();
	for (auto& thread : m_pool)
	{
		thread.join();//等到目标线程退出 在往下执行
	}

}

void ThreadPool::PollTask()
{
	while (m_active)
	{
		std::unique_lock<std::mutex> lock(m_globalLock);
		while (m_tasks.empty() && m_active)
		{
			m_monitor.wait(lock);
		}

		if (!m_tasks.empty())
		{
			std::unique_ptr<IRunable> task = std::move(m_tasks.front());
			m_tasks.pop();
			lock.unlock();

			task->Run();
		}
		else
		{
			lock.unlock();
		}
	}
}
