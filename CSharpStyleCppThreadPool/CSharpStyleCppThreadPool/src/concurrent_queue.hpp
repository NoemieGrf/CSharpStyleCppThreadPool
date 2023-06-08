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
        
        void Enqueue(T pData)
        {
            std::lock_guard lockGuard(_mutex);
            _queue.push(pData);
            _condVar.notify_one();
        }
        
        T WaitDequeue()
        {
            std::unique_lock lockGuard(_mutex);
            _condVar.wait(lockGuard, [this]
            {
                return !_queue.empty();
            });
            
            auto value = _queue.front();
            _queue.pop();
            return value;
        }

        bool TryDequeue(T* result)
        {
            std::lock_guard lockGuard(_mutex);
            if (_queue.empty())
                return false;

            auto value = _queue.front();
            _queue.pop();
            *result = value;
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

    template<typename T>
    class CasConcurrentQueue
    {
    private:
        struct Node
        {
            T* data;
            std::atomic<Node*> next;
            
            Node(T* data_) : data(data_)
            {
            }
        };
        
    public:
        void Enqueue(T* data)
        {
            Node newNode = new Node(data);
            Node* currentTail = _tail.load();
            while (!currentTail->next.compare_exchange_weak(nullptr, &newNode))
            {
                // ...
            }
            
            _tail.compare_exchange_weak(currentTail, &newNode);
        }
        
        T* Dequeue()
        {
            Node* currentHead = _head.load();
            while (currentHead && !_head.compare_exchange_weak(currentHead, currentHead->next))
            {
                currentHead = _head.load();
            }
            
            return currentHead ? currentHead->data : nullptr;
        }

    private:
        std::atomic<Node*> _head;
        std::atomic<Node*> _tail;
    };


}