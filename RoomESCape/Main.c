#include "Main.h"

bool hasExitRenderThread;
bool hasLoadComplete;
bool isDownESC;

int main()
{
    SetConsoleTitle(TEXT("R-ESC"));
    system("mode con:cols=200 lines=50");

    // Thread
    HANDLE threads[THREAD_COUNT];
    int threadIDs[THREAD_COUNT];

    threadIDs[THREAD_GAME] = THREAD_GAME;
    threads[THREAD_GAME] = (HANDLE)_beginthreadex(NULL, 0, &PlayGame_thread, &threadIDs[THREAD_GAME], 0, NULL);

    threadIDs[THREAD_RENDER] = THREAD_RENDER;
    threads[THREAD_RENDER] = (HANDLE)_beginthreadex(NULL, 0, &RenderDisplay_thread, &threadIDs[THREAD_RENDER], 0, NULL);

    // Wait Other Threads
    WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);

    // Thread Release
    CloseHandle(threads[THREAD_GAME]);
    CloseHandle(threads[THREAD_RENDER]);

    return 0;
}

unsigned int _stdcall PlayGame_thread()
{
    InitializeGame();

    // Main Game Loop
    while (true)
    {
        // turn time?
        /*if (turn < MAX_TURN)
        {
            break;
        }
        turn++;*/

        if (_kbhit())
        {
            if (GetKeyInput() == -1)
            {
                isDownESC = true;
                break;
            }
        }

        UpdateGame();

        ProcessGame();
        WaitGame();     // Set FPS
    }

    while (hasExitRenderThread == false)
    {
        // Wait Release RenderThread
    }

    ReleaseGame();
    fprintf(stdout, "gameThread exit\n");

    return 0;
}

unsigned int _stdcall RenderDisplay_thread()
{
    InitializeScreen();

    // Main Render Loop
    while (true)
    {
        if (isDownESC)
        {
            break;
        }

        RenderScreen();

        WaitRenderScreen(&isDownESC);
    }
    
    ReleaseScreen();
    fprintf(stdout, "renderThread exit\n");

    return 0;
}