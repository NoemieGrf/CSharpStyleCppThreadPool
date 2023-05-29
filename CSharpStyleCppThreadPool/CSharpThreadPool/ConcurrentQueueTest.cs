using System;
using System.Collections.Concurrent;

namespace CSharpThreadPool
{
    internal class ConcurrentQueueTest
    {
        ConcurrentQueue<int> _concurrentQueue = new ConcurrentQueue<int>();

        public void Run()
        {
            Thread thread1 = new Thread(ThreadWrite1);
            Thread thread2 = new Thread(ThreadWrite2);
            Thread threadRead = new Thread(ThreadRead);

            thread1.Start();
            thread2.Start();
            threadRead.Start();

            thread1.Join();
            thread2.Join();
            threadRead.Join();
        }

        private void ThreadWrite1()
        {
            for (int i = 0; i < 100; ++i)
            {
                _concurrentQueue.Enqueue(i);
                Thread.Sleep(100);
            }
        }

        private void ThreadWrite2()
        {
            for (int i = 101; i < 200; ++i)
            {
                _concurrentQueue.Enqueue(i);
                Thread.Sleep(50);
            }
        }

        private void ThreadRead()
        {
            while (_concurrentQueue.Count > 0)
            {
                if (_concurrentQueue.TryDequeue(out var number))
                {
                    Console.WriteLine(number);
                    Thread.Sleep(150);
                }
            }
            
        }
    }
}
