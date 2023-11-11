#include <stdio.h>
#include <Windows.h>

#include "GameManager.h"
#include "RenderManager.h"

static int frameCount;
static char* frameTextBuffer;
static clock_t frameCurTime, frameOldTime;

static int screenIndex;
static HANDLE screenBuffer[2];

static int height = 40;
static int chartIndex = 0;
static Chart* chart;

void InitializeScreen()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	// SetConsoleCP(CP_WINANSI);          // Set the console input  code page to UTF-8
	// SetConsoleOutputCP(CP_WINANSI);    // Set the console output code page to UTF-8

	screenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	HideCursor();

	while (hasLoadComplete == false)
	{
		// PrintScreen(0, 1, "Json Data is Loading from Web...");
	}

	system("cls");					// Render Clear - exe error

	// Chart Data Initialize
	chart = (Chart*)malloc(sizeof(Chart));
	chart->lineInfoes = (LineInfo**)malloc(sizeof(LineInfo*) * MAX_BUFFER_SIZE);
	chart->curTurn = -1;
	chart->size = MAX_BUFFER_SIZE;
	for (int i = 0; i < chart->size; i++)
	{
		chart->lineInfoes[i] = (LineInfo*)malloc(sizeof(LineInfo));
	}

	frameCount = 0;
	frameTextBuffer = (char*)malloc(sizeof(char) * FRAME_BUFFER_SIZE);
	sprintf(frameTextBuffer, "FPS: %3d", frameCount);
	frameOldTime = clock();
}

void RenderScreen()
{
	ClearScreen();

	int value = corporation->stocks[turn].closingPrice - corporation->stocks[turn].startingPrice;
	value /= 100;

	// Render Screen Logic
	if (chart->curTurn < turn)
	{
		chart->curTurn = turn;

		if (0 < value)
		{
			chart->lineInfoes[chartIndex]->createdTurn = turn;
			chart->lineInfoes[chartIndex]->height = height;
			strcpy(chart->lineInfoes[chartIndex]->character, "¦°");
			chartIndex++;
			height--;

			for (int i = 2; i < value; i++)
			{
				chart->lineInfoes[chartIndex]->createdTurn = turn;
				chart->lineInfoes[chartIndex]->height = height;
				strcpy(chart->lineInfoes[chartIndex]->character, "¦­");
				chartIndex++;
				height--;
			}

			chart->lineInfoes[chartIndex]->createdTurn = turn;
			chart->lineInfoes[chartIndex]->height = height;
			strcpy(chart->lineInfoes[chartIndex]->character, "¦®");
			chartIndex++;

		}
		else if (value < 0)
		{
			chart->lineInfoes[chartIndex]->createdTurn = turn;
			chart->lineInfoes[chartIndex]->height = height;
			strcpy(chart->lineInfoes[chartIndex]->character, "¦¯");
			chartIndex++;
			height++;

			for (int i = 2; i < (-1 * value); i++)
			{
				chart->lineInfoes[chartIndex]->createdTurn = turn;
				chart->lineInfoes[chartIndex]->height = height;
				strcpy(chart->lineInfoes[chartIndex]->character, "¦­");
				chartIndex++;
				height++;
			}

			chart->lineInfoes[chartIndex]->createdTurn = turn;
			chart->lineInfoes[chartIndex]->height = height;
			strcpy(chart->lineInfoes[chartIndex]->character, "¦±");
			chartIndex++;
		}
		else
		{
			chart->lineInfoes[chartIndex]->createdTurn = turn;
			chart->lineInfoes[chartIndex]->height = height;
			strcpy(chart->lineInfoes[chartIndex]->character, "¦¬");
			chartIndex++;
		}
	}

	// Render - column
	for (int i = 0; i < chartIndex; i++)
	{
		PrintScreen(SCREEN_WIDTH - turn + chart->lineInfoes[i]->createdTurn, chart->lineInfoes[i]->height, chart->lineInfoes[i]->character);
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		char lineCount[SCREEN_HEIGHT];
		sprintf(lineCount, "%2d\n", i);
		PrintScreen(0, i+1, lineCount);
	}

	CheckFrameScreen();

	char valueBuffer[5];
	sprintf(valueBuffer, "%4d", value);
	PrintScreen(SCREEN_WIDTH - 5, 1, valueBuffer);

	FlippingScreen();
}

void ClearScreen()
{
	COORD coord = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(screenBuffer[screenIndex], ' ', SCREEN_WIDTH * SCREEN_HEIGHT, coord, &dw);
}

void FlippingScreen()
{
	SetConsoleActiveScreenBuffer(screenBuffer[screenIndex]);
	screenIndex = (screenIndex == 0) ? 1 : 0;
}

void CheckFrameScreen()
{
	frameCount++;
	frameCurTime = clock();
	if (1000 <= frameCurTime - frameOldTime)
	{
		sprintf(frameTextBuffer, "FPS: %3d", frameCount);
		frameOldTime = clock();
		frameCount = 0;
	}

	PrintScreen(SCREEN_WIDTH - FRAME_BUFFER_SIZE, 0, frameTextBuffer);
}

void WaitRenderScreen()
{
	while (true)
	{
		if (33 < sharedCurTime - sharedOldTime || isDownESC)
		{
			return;
		}
	}
}

void ReleaseScreen()
{
	CloseHandle(screenBuffer[0]);
	CloseHandle(screenBuffer[1]);

	free(frameTextBuffer);

	for (int i = 0; i < chart->size; i++)
	{
		free(chart->lineInfoes[i]);
	}
	free(chart->lineInfoes);
	free(chart);

	hasExitRenderThread = true;
}

void PrintScreen(int x, int y, char* string)
{
	DWORD dw;
	COORD cursorPosition = { x, y };
	SetConsoleCursorPosition(screenBuffer[screenIndex], cursorPosition);
	WriteFile(screenBuffer[screenIndex], string, strlen(string), &dw, NULL);
}

void SetColor(int fgColor, int bgColor)
{
	SetConsoleTextAttribute(screenBuffer[screenIndex], fgColor | bgColor << BLACK);
}

void HideCursor(void)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = 0;

	GetConsoleCursorInfo(screenBuffer[0], &cursorInfo);
	SetConsoleCursorInfo(screenBuffer[0], &cursorInfo);

	GetConsoleCursorInfo(screenBuffer[1], &cursorInfo);
	SetConsoleCursorInfo(screenBuffer[1], &cursorInfo);
}