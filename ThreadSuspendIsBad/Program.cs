using System;
using System.Threading;

namespace ThreadSuspendIsBad
{
    public static class Program
    {
        public static void Main()
        {
            Thread helloThread = new Thread(HelloThreadEntry);
            helloThread.Start();

            while (true)
            {
                Console.WriteLine("Suspending sibling thread...");
                helloThread.Suspend();
                Console.WriteLine("Resuming sibling thread...");
                helloThread.Resume();
            }
        }

        private static void HelloThreadEntry()
        {
            while (true)
            {
                Console.WriteLine("Hello, world!");
            }
        }
    }
}
