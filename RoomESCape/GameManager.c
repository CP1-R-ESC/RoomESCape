#include <time.h>
#include <conio.h>
#include <stdlib.h>

#include "GameManager.h"
#include "Web.h"

char* url;
char* jsonData;
Corporation* corporation;
int day;

clock_t sharedCurTime, sharedOldTime;

static clock_t curTime, oldTime;

void InitializeGame()
{
	// JsonData Initialize
	url = InitializeURL(SAMSUNG_ELECTRONICS, "20200000", "20210000");
	jsonData = PostWebRequest(url);
	corporation = InitializeJSON(jsonData);

	hasLoadComplete = true;

	// Turn Initialize
	int turn = 0;
	const int MAX_TURN = corporation->stockCount;

	// JsonData Release
	free(url);
	free(jsonData);

	// Time Initialize
	sharedOldTime = clock();
	oldTime = clock();
	day = 0;
}

void UpdateGame()
{
	
}

void ProcessGame()
{
	curTime = clock();
	if (2000 <= curTime - oldTime)
	{
		oldTime = clock();
		day++;
	}
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