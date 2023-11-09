#include <time.h>
#include <conio.h>

#include "GameManager.h"
#include "RenderManager.h"

void InitializeGame()
{
	ScreenInitialize();

	srand(time(NULL));
}

void UpdateGame()
{

}

void RenderGame()
{
	ScreenClear();

	ScreenFlipping();
}

void WaitGame(clock_t oldTime)
{
	clock_t curTime;
	while (TRUE)
	{
		curTime = clock();
		if (33 < curTime - oldTime)
		{
			break;
		}
	}

	return;
}

void ReleaseGame()
{
	ScreenRelease();
}

void GetKeyInput()
{
	int nKey = _getch();

	if (nKey == KEY_ESC)
	{
		exit(0);
	}

	switch (nKey)
	{
	case 'q':
		break;
	case 'w':
		break;
	case 'e':
		break;


	default:
		break;
	}
}