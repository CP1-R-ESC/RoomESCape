#include <time.h>
#include <conio.h>
#include <stdlib.h>

#include "GameManager.h"
#include "Web.h"

char* url;
char* jsonData;
Corporation* corporation;
int turn;
int maxTurn;

clock_t sharedCurTime, sharedOldTime;

static clock_t curTime, oldTime;

bool InitializeGame()
{
	// JsonData Initialize
	url = InitializeURL(SAMSUNG_ELECTRONICS, "20200000", "20210000");
	jsonData = PostWebRequest(url);
	corporation = InitializeJSON(jsonData);
	if (corporation == NULL)
		return false;

	hasLoadComplete = true;

	// Turn Initialize
	turn = 0;
	maxTurn = corporation->stockCount - 1;

	// JsonData Release
	free(url);
	free(jsonData);

	// Time Initialize
	sharedOldTime = clock();
	oldTime = clock();

	return true;
}

void UpdateGame()
{

}

bool ProcessGame()
{
	curTime = clock();
	if (100 <= curTime - oldTime)
	{
		oldTime = clock();

		if (turn == maxTurn)
		{
			return false;
		}

		turn++;
	}

	return true;
}

void WaitGame()
{
	while (TRUE)
	{
		sharedCurTime = clock();
		if (33 < sharedCurTime - sharedOldTime)
		{
			sharedOldTime = clock();
			return;
		}
	}
}

void ReleaseGame()
{
	// Corporation Release
	free(corporation->name);
	free(corporation->stocks);
	free(corporation);
}

int GetKeyInput()
{
	int nKey = _getch();

	if (nKey == KEY_ESC)
	{
		return -1;
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