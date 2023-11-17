#include "Main.h"

bool hasExitRenderThread;
bool hasLoadComplete;
bool isDownESC;

int main()
{
    SetConsoleTitle(TEXT("R-ESC"));
    system("mode con:cols=250 lines=60");

    // Thread - 여기서 두 쓰레드 모두 게임 프레임워크 구조를 채택함
    HANDLE threads[THREAD_COUNT];   // 쓰레드 배열
    int threadIDs[THREAD_COUNT];    // 각 쓰레드의 ID

    threadIDs[THREAD_GAME] = THREAD_GAME;
    threads[THREAD_GAME] = (HANDLE)_beginthreadex(NULL, 0, &PlayGame_thread, &threadIDs[THREAD_GAME], 0, NULL);             // Game Thread 실행

    threadIDs[THREAD_RENDER] = THREAD_RENDER;
    threads[THREAD_RENDER] = (HANDLE)_beginthreadex(NULL, 0, &RenderDisplay_thread, &threadIDs[THREAD_RENDER], 0, NULL);    // Render Thread 실행

    // Wait Other Threads
    WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);  // 다른 Thread가 끝나는 것을 기다림 

    // Thread Release
    CloseHandle(threads[THREAD_GAME]);      // 생성했던 2개의 Thread를 해제
    CloseHandle(threads[THREAD_RENDER]);

    return 0;   // 프로그램 종료
}

unsigned int _stdcall PlayGame_thread()
{
    if (InitializeGame() == false)  // curl 라이브러리를 활용하여 웹 통신, JSON 파일을 받아와 데이터를 힙 메모리 상에 저장
    {
        return -1;
    }
    

    // Main Game Loop
    while (true)
    {
        if (_kbhit())   // 키보드가 눌렸는가
        {
            if (GetKeyInput() == -1)    // ESC를 눌렀다면
            {
                isDownESC = true;
                break;                  // Main Game Loop를 탈출
            }
        }

        UpdateGame();   // empty func

        if (ProcessGame() == false) // 현재 턴을 증가시킴
        {
            isDownESC = true;
            break;
        }


        WaitGame();     // Frame Per Sec를 조정하기 위해 잠시 대기하는 함수
    }

    while (hasExitRenderThread == false)
    {
        // Wait Release RenderThread
    }

    ReleaseGame();  // 힙 메모리 상에 있던 JSON 데이터를 해제하는 함수
    fprintf(stdout, "gameThread exit\n");

    return 0;
}

unsigned int _stdcall RenderDisplay_thread()
{
    InitializeScreen(); // console screen과 관련된 초기화 (더블버퍼링, 커서 숨기기, 라인 넘버 출력)

    // Main Render Loop
    while (true)
    {
        if (isDownESC)
        {
            break;  // Game Thread에서 ESC를 눌렀다는 것이 확인 되면 Main Render Loop를 탈출
        }

        RenderScreen(); //  화면 상에 Game Thread에서 가져온 데이터를 기반으로 시각화

        WaitRenderScreen(); // 프레임률을 보장하기 위해서 대기하는 함수
    }
    
    ReleaseScreen();    // 콘솔 스크린에 동적으로 할당한 버퍼 및 데이터들을 해제하는 함수
    fprintf(stdout, "renderThread exit\n");

    return 0;
}