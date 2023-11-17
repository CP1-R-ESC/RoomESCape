#include "Main.h"

bool hasExitRenderThread;
bool hasLoadComplete;
bool isDownESC;

int main()
{
    SetConsoleTitle(TEXT("R-ESC"));
    system("mode con:cols=250 lines=60");

    // Thread - ���⼭ �� ������ ��� ���� �����ӿ�ũ ������ ä����
    HANDLE threads[THREAD_COUNT];   // ������ �迭
    int threadIDs[THREAD_COUNT];    // �� �������� ID

    threadIDs[THREAD_GAME] = THREAD_GAME;
    threads[THREAD_GAME] = (HANDLE)_beginthreadex(NULL, 0, &PlayGame_thread, &threadIDs[THREAD_GAME], 0, NULL);             // Game Thread ����

    threadIDs[THREAD_RENDER] = THREAD_RENDER;
    threads[THREAD_RENDER] = (HANDLE)_beginthreadex(NULL, 0, &RenderDisplay_thread, &threadIDs[THREAD_RENDER], 0, NULL);    // Render Thread ����

    // Wait Other Threads
    WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);  // �ٸ� Thread�� ������ ���� ��ٸ� 

    // Thread Release
    CloseHandle(threads[THREAD_GAME]);      // �����ߴ� 2���� Thread�� ����
    CloseHandle(threads[THREAD_RENDER]);

    return 0;   // ���α׷� ����
}

unsigned int _stdcall PlayGame_thread()
{
    if (InitializeGame() == false)  // curl ���̺귯���� Ȱ���Ͽ� �� ���, JSON ������ �޾ƿ� �����͸� �� �޸� �� ����
    {
        return -1;
    }
    

    // Main Game Loop
    while (true)
    {
        if (_kbhit())   // Ű���尡 ���ȴ°�
        {
            if (GetKeyInput() == -1)    // ESC�� �����ٸ�
            {
                isDownESC = true;
                break;                  // Main Game Loop�� Ż��
            }
        }

        UpdateGame();   // empty func

        if (ProcessGame() == false) // ���� ���� ������Ŵ
        {
            isDownESC = true;
            break;
        }


        WaitGame();     // Frame Per Sec�� �����ϱ� ���� ��� ����ϴ� �Լ�
    }

    while (hasExitRenderThread == false)
    {
        // Wait Release RenderThread
    }

    ReleaseGame();  // �� �޸� �� �ִ� JSON �����͸� �����ϴ� �Լ�
    fprintf(stdout, "gameThread exit\n");

    return 0;
}

unsigned int _stdcall RenderDisplay_thread()
{
    InitializeScreen(); // console screen�� ���õ� �ʱ�ȭ (������۸�, Ŀ�� �����, ���� �ѹ� ���)

    // Main Render Loop
    while (true)
    {
        if (isDownESC)
        {
            break;  // Game Thread���� ESC�� �����ٴ� ���� Ȯ�� �Ǹ� Main Render Loop�� Ż��
        }

        RenderScreen(); //  ȭ�� �� Game Thread���� ������ �����͸� ������� �ð�ȭ

        WaitRenderScreen(); // �����ӷ��� �����ϱ� ���ؼ� ����ϴ� �Լ�
    }
    
    ReleaseScreen();    // �ܼ� ��ũ���� �������� �Ҵ��� ���� �� �����͵��� �����ϴ� �Լ�
    fprintf(stdout, "renderThread exit\n");

    return 0;
}