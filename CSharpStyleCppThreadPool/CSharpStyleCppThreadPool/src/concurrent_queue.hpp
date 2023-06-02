#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

#include <Windows.h>

namespace Grf
{
    template<typename T>
    class LockConcurrentQueue
    {
    public:
        LockConcurrentQueue()
        {
        }
        
        void Push(T data)
        {
            std::lock_guard lockGuard(_mutex);
            _queue.push(std::move(data));
            _condVar.notify_one();
        }
        
        void WaitAndPop(T& value)
        {
            std::unique_lock lockGuard(_mutex);
            _condVar.wait(lockGuard, [this]{
                return !_queue.empty();
            });
            
            value = std::move(_queue.front());
            _queue.pop();
        }
        
        bool TryPop(T& value)
        {
            std::lock_guard lockGuard(_mutex);
            if (_queue.empty())
                return false;
            
            value = std::move(_queue.front());
            _queue.pop();
            return true;
        }
        
        bool Empty() const
        {
            std::lock_guard lockGuard(_mutex);
            return _queue.empty();
        }

    private:
        mutable std::mutex _mutex;  // mutable for const function
        std::queue<T> _queue;
        std::condition_variable _condVar;
    };

}