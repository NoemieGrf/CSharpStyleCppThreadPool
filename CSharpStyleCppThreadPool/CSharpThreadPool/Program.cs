
using CSharpThreadPool;
using System;
using System.Threading;

namespace ThreadPoolTest
{
    class Program
    {
        static void Main(string[] args)
        {
            // ConcurrentQueueTest concurrentQueueTest = new ConcurrentQueueTest();
            // concurrentQueueTest.Run();

            ResetEventTest resetEventTest = new ResetEventTest();
            resetEventTest.Run();

            /*
            WaitHandle[] waitHandles = new WaitHandle[]
            {
                new ManualResetEvent(false),
                new ManualResetEvent(false)
            };
            */
        }


        public static void MyMethod(object obj)
        {
            Thread thread = Thread.CurrentThread;
            string message = $"Background: {thread.IsBackground}, Thread Pool: {thread.IsThreadPoolThread}, Thread ID: {thread.ManagedThreadId}";
            Console.WriteLine(message);
        }

    }
}