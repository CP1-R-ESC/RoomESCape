#include "Main.h"

int main()
{
    InitializeGame();

    clock_t curTime, oldTime;

    char* url = InitializeURL(SAMSUNG_ELECTRONICS, "20200000", "20210000");
    char* jsonData = PostWebRequest(url);
    Corporation* corporation = InitializeJSON(jsonData);

    int turn = 0;
    const int MAX_TURN = corporation->stockCount;

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
            GetKeyInput();
        }

        UpdateGame();
        RenderGame();
        
        WaitGame(clock());  // Set FPS
    }

    free(url);
    free(jsonData);
    free(corporation->name);
    free(corporation->stocks);
    free(corporation);
    ReleaseGame();

    return 0;
}