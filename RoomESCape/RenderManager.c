#include <stdio.h>
#include <Windows.h>

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

	SetConsoleCP(CP_UTF8);          // Set the console input  code page to UTF-8
	SetConsoleOutputCP(CP_UTF8);    // Set the console output code page to UTF-8

	system("cls");					// Render Clear

	frameCount = 0;
	frameTextBuffer = (char*)malloc(sizeof(char) * FRAME_BUFFER_SIZE);
	sprintf(frameTextBuffer, "FPS: %3d", frameCount);
	frameOldTime = clock();
}

void RenderScreen()
{
	ClearScreen();

	// Render Screen Logic
	{

	}

	CheckFrameScreen();

	FlippingScreen();
}

void ClearScreen()
{
	COORD coord = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(screenBuffer[screenIndex], ' ', 80 * 25, coord, &dw);
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

void WaitRenderScreen(clock_t oldTime)
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

void ReleaseScreen()
{
	CloseHandle(screenBuffer[0]);
	CloseHandle(screenBuffer[1]);

	free(frameTextBuffer);
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

void GotoCoordinate(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}