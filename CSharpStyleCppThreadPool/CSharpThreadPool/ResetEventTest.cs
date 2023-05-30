

namespace CSharpThread
{
    public class ResetEventTest
    {
        private AutoResetEvent _autoResetEvent = new AutoResetEvent(false);
        // private ManualResetEvent _manualResetEvent = new ManualResetEvent(false);

        private int _currentNumber = 0;
        private bool _shouldThreadStop = false;

        public void Run()
        { 
            Console.WriteLine("Auto Reset Event: ");

            Thread autoResetThread = new Thread(ThreadJob);
            autoResetThread.Start();

            for (int i = 1; i < 15; i++)
            {
                Console.Write(i);
                Console.Write(' ');
                _currentNumber = i;
                _autoResetEvent.Set();
                Thread.Sleep(100);
            }

            Console.WriteLine();

            _shouldThreadStop = true;
            _autoResetEvent.Set();

            autoResetThread.Join();
        }

        private void ThreadJob()
        {
            while (true)
            {
                _autoResetEvent.WaitOne();

                Thread.Sleep(150);

                if (_shouldThreadStop)
                    break;

                Console.Write(_currentNumber);
                Console.Write(' ');
            }
        }
    }
}
