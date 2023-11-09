#include <stdio.h>
#include <Windows.h>

#include "GameManager.h"
#include "RenderManager.h"

static int frameCount;
static char* frameTextBuffer;
static clock_t frameCurTime, frameOldTime;

static int screenIndex;
static HANDLE screenBuffer[2];

void InitializeScreen()
{
	screenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	HideCursor();

	SetConsoleCP(CP_WINANSI);          // Set the console input  code page to UTF-8
	SetConsoleOutputCP(CP_WINANSI);    // Set the console output code page to UTF-8

	while (hasLoadComplete == false)
	{
		PrintScreen(0, 0, "Json Data is Loading from Web...");
	}

	system("cls");					// Render Clear
	
	frameCount = 0;
	frameTextBuffer = (char*)malloc(sizeof(char) * FRAME_BUFFER_SIZE);
	sprintf(frameTextBuffer, "FPS: %3d", frameCount);
	frameOldTime = clock();
}

void RenderScreen()
{
	ClearScreen();

	PrintScreen(25, 25, "收收收收收收收收收收收收");
	// Render Screen Logic
	/*{
		int height = corporation->stocks[day].startingPrice < corporation->stocks[day].closingPrice;
		height %= 100;
		if (0 < height)
		{
			for (int i = 0; i < height; i++)
			{

			}
		}
	}*/

	CheckFrameScreen();

	FlippingScreen();
}

void ClearScreen()
{
	COORD coord = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(screenBuffer[screenIndex], ' ', 200 * 50, coord, &dw);
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

	PrintScreen(0, 0, frameTextBuffer);
}

void WaitRenderScreen()
{
	while (TRUE)
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