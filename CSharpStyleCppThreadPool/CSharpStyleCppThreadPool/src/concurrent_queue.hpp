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
        struct Node
        {
            T data;
            std::atomic<Node*> next;
            
            Node(T data_) : data(data_)
            {
            }
        };
        
    public:
        void Enqueue(T data)
        {
            Node node = new Node{ data };

            Node* head = _head.load();
            Node* tail = _tail.load();

            while (head == nullptr && tail == nullptr)
            {
                
            }
            
            Node* currentTail = _tail.load();
            
            while (true)
            {
                if (currentTail->next.compare_exchange_weak(nullptr, &node))
                    break;

                // update current tail
                currentTail = _tail.load();
            }
            
            _tail.compare_exchange_weak(currentTail, &node);
        }
        
        bool TryDequeue(T* result)
        {
            Node* currentHead = _head.load();

            if (currentHead == nullptr)
                return false;

            while (true)
            {
                if (_head.compare_exchange_weak(currentHead, currentHead->next))
                    break;

                // update current head
                currentHead = _head.load();
            }

            if (currentHead == nullptr)
                return false;

            *result = currentHead->data;
            return true;
        }

        bool Empty() const
        {
            
        }

    private:
        std::atomic<Node*> _head = nullptr;
        std::atomic<Node*> _tail = nullptr;
        size_t _count = 0;
    };


}