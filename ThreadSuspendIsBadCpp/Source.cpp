#include <stdio.h>
#include <Windows.h>

static DWORD WINAPI HelloThreadEntry(LPVOID threadParameter);
static volatile BOOL helloThreadIsRunning;

int main()
{
    HANDLE helloThread = CreateThread(NULL, 0, HelloThreadEntry, NULL, 0, NULL);
    
    // The example sometimes runs so fast that you might not even get a single "Hello, world!" out the door before the deadlock happens.
    // This doesn't happen in .NET land, probably because there's more layers of stuff happening in Console.WriteLine or because Thread.Suspend is more complicated.
    while (!helloThreadIsRunning)
    { }

    while (true)
    {
        printf("Suspending sibling thread...\n");
        SuspendThread(helloThread);
        printf("Resuming sibling thread...\n");
        ResumeThread(helloThread);
    }
}

static DWORD WINAPI HelloThreadEntry(LPVOID threadParameter)
{
    while (true)
    {
        printf("Hello, world!\n");
        helloThreadIsRunning = TRUE;
    }
}
