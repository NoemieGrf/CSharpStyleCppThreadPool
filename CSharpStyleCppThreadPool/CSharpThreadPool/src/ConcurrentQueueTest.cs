using System;
using System.Collections.Concurrent;

/*
 * ConcurrentQueue 线程安全队列
 */

namespace CSharpThread
{
    public class ConcurrentQueueTest
    {
        private Queue<int> _unsafeQueue = new Queue<int>();
        private ConcurrentQueue<int> _safeQueue = new ConcurrentQueue<int>();

        public void Run()
        {
            Console.WriteLine("Thread Not Safe Queue: ");

            Thread unsafeThread1 = new Thread(NotSafeThreadWrite1);
            Thread unsafeThread2 = new Thread(NotSafeThreadWrite2);

            unsafeThread1.Start();
            unsafeThread2.Start();

            unsafeThread1.Join();
            unsafeThread2.Join();

            while (_unsafeQueue.Count > 0)
            {
                if (_unsafeQueue.TryDequeue(out var number))
                {
                    Console.Write(number);
                    Console.Write(' ');
                }
            }

            Console.WriteLine();

            Console.WriteLine("Thread Safe Queue: ");

            Thread safeThread1 = new Thread(SafeThreadWrite1);
            Thread safeThread2 = new Thread(SafeThreadWrite2);

            safeThread1.Start();
            safeThread2.Start();

            safeThread1.Join();
            safeThread2.Join();

            while (_safeQueue.Count > 0)
            {
                if (_safeQueue.TryDequeue(out var number))
                {
                    Console.Write(number);
                    Console.Write(' ');
                }
            }
        }

        private void NotSafeThreadWrite1()
        {
            for (int i = 0; i < 10; ++i)
            {
                _unsafeQueue.Enqueue(i);
                Thread.Sleep(50);
            }
        }

        private void NotSafeThreadWrite2()
        {
            for (int i = 0; i < 10; ++i)
            {
                _unsafeQueue.Enqueue(i);
                Thread.Sleep(50);
            }
        }

        private void SafeThreadWrite1()
        {
            for (int i = 0; i < 10; ++i)
            {
                _safeQueue.Enqueue(i);
                Thread.Sleep(50);
            }
        }

        private void SafeThreadWrite2()
        {
            for (int i = 0; i < 10; ++i)
            {
                _safeQueue.Enqueue(i);
                Thread.Sleep(50);
            }
        }
    }
}
