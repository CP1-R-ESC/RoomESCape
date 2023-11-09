#include <time.h>
#include <conio.h>
#include <stdlib.h>

#include "GameManager.h"

void InitializeGame()
{
	
}

void UpdateGame()
{

}

void WaitGame(clock_t oldTime)
{
	clock_t curTime;
	while (TRUE)
	{
		curTime = clock();
		if (33 < curTime - oldTime)
		{
			return;
		}
	}
}

void ReleaseGame()
{
	
}

int GetKeyInput()
{
	int nKey = _getch();

	if (nKey == KEY_ESC)
	{
		return 1;
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

	return 0;
}