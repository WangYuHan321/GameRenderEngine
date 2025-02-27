#pragma once
#include "../Render/Resource/Loader/Async/FileJob.h"
#include "WinThread.h"

#include <queue>
#include <mutex>
#include <condition_variable>
#undef max
template<typename T>
class SafeQueue {
public:
    explicit SafeQueue(size_t max_capacity = std::numeric_limits<size_t>::max()) :max_capacity_(max_capacity)
    {};
    ~SafeQueue()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.notify_all();
    }
    SafeQueue(const SafeQueue&) = delete;
    SafeQueue& operator=(const SafeQueue&) = delete;
    SafeQueue(SafeQueue&&) = delete;

    template<typename U>
    void push(U&& value)  //perfect forwarding,support push lvalue and rvalue
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::forward<U>(value));
        condition_.notify_one();
    }

    bool timeout_pop(T& value, std::uint64_t timeout_ms)  // timeout block pop
    {
        std::unique_lock<std::mutex> lock(mutex_);
        bool ret = condition_.wait_for(lock, std::chrono::milliseconds(timeout_ms), [this] { return !queue_.empty(); });
        if (ret) //Î´³¬Ê±
        {
            if (!queue_.empty())
            {
                value = std::move(queue_.front());
                queue_.pop();
                return true;
            }
        }
        return false;
    }


    void pop(T& value) //block pop
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !queue_.empty(); });
        if (!queue_.empty())
        {
            value = std::move(queue_.front());
            queue_.pop();
        }
    }

    bool try_pop(T& value) //nonblock pop
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!queue_.empty())
        {
            value = std::move(queue_.front());
            queue_.pop();
            return true;
        }
        return false;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    std::size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
    size_t max_capacity_;
};

#undef AddJob

class AsynJobThread : public WinThread
{
public:
	AsynJobThread();
	virtual ~AsynJobThread();

    void SafeAddJob(AsyncJob* job);
	void Run();

protected:
	virtual string GetThreadName()const;
    SafeQueue<AsyncJob*> m_pResourceQueue;
};

