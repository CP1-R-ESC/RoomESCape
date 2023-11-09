#include "Main.h"

char* url;
char* jsonData;
Corporation* corporation;

static bool isDownESC;

int main()
{
    // Thread
    HANDLE threads[THREAD_COUNT];
    int threadIDs[THREAD_COUNT];

    threadIDs[THREAD_GAME] = THREAD_GAME;
    threads[THREAD_GAME] = (HANDLE)_beginthreadex(NULL, 0, &PlayGame_thread, &threadIDs[THREAD_GAME], 0, NULL);

    threadIDs[THREAD_RENDER] = THREAD_RENDER;
    threads[THREAD_RENDER] = (HANDLE)_beginthreadex(NULL, 0, &RenderDisplay_thread, &threadIDs[THREAD_RENDER], 0, NULL);

    // JsonData Initialize
    url = InitializeURL(SAMSUNG_ELECTRONICS, "20200000", "20210000");
    jsonData = PostWebRequest(url);
    corporation = InitializeJSON(jsonData);

    // JsonData Release
    free(url);
    free(jsonData);

    // Turn Initialize
    int turn = 0;
    const int MAX_TURN = corporation->stockCount;

    // Wait Other Threads
    WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);

    // Thread Release
    CloseHandle(threads[THREAD_GAME]);
    CloseHandle(threads[THREAD_RENDER]);

    // Corporation Release
    free(corporation->name);
    free(corporation->stocks);
    free(corporation);

    return 0;
}

unsigned int _stdcall PlayGame_thread()
{
    InitializeGame();

    // Main Game Loop
    while (TRUE)
    {
        // turn time?
        /*if (turn < MAX_TURN)
        {
            break;
        }
        turn++;*/

        if (_kbhit())
        {
            if (GetKeyInput() == 1)
            {
                isDownESC = true;
                break;
            }
        }

        UpdateGame();

        WaitGame(clock());  // Set FPS
    }

    ReleaseGame();

    return 0;
}

unsigned int _stdcall RenderDisplay_thread()
{
    InitializeScreen();

    while (TRUE)
    {
        if (isDownESC)
        {
            break;
        }

        RenderScreen();

        WaitRenderScreen(clock());
    }
    
    ReleaseScreen();

    return 0;
}

void LoadJsonData()
{
    char* url = InitializeURL(SAMSUNG_ELECTRONICS, "20200000", "20210000");
    char* jsonData = PostWebRequest(url);
    Corporation* corporation = InitializeJSON(jsonData);

    int turn = 0;
    const int MAX_TURN = corporation->stockCount;

    free(url);
    free(jsonData);
    free(corporation->name);
    free(corporation->stocks);
    free(corporation);
}