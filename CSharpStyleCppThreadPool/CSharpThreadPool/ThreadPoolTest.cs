

namespace CSharpThread
{
    public class ThreadPoolTest
    {
        public void Run() 
        {
            int num = 10;
            CountdownEvent countDownEvent = new CountdownEvent(num);

            for (int i = 0; i < num; i++)
            {
                ThreadPool.QueueUserWorkItem(new WaitCallback((object? obj) =>
                {
                    ThreadJob(obj, countDownEvent);
                }));
            }

            countDownEvent.Wait();
        }

        public void ThreadJob(object? obj, CountdownEvent countDownEvent)
        {
            Thread thread = Thread.CurrentThread;
            string message = $"Background: {thread.IsBackground}, Thread Pool: {thread.IsThreadPoolThread}, Thread ID: {thread.ManagedThreadId}";
            Console.WriteLine(message);
            countDownEvent.Signal();
        }
    }
}
