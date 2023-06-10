

using System;
using System.Threading;

namespace CSharpThread
{
    class Program
    {
        static void Main(string[] args)
        {
            ConcurrentQueueTest concurrentQueueTest = new ConcurrentQueueTest();
            concurrentQueueTest.Run();

            ResetEventTest resetEventTest = new ResetEventTest();
            resetEventTest.Run();

            ThreadPoolTest threadPoolTest = new ThreadPoolTest();
            threadPoolTest.Run();
        }

    }
}