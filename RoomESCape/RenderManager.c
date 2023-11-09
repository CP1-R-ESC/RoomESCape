#include <Windows.h>

#include "RenderManager.h"

static int screenIndex;
static HANDLE screenBuffer[2];

void ScreenInitialize()
{
	screenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	HideCursor();

	SetConsoleCP(CP_UTF8);          // Set the console input  code page to UTF-8
	SetConsoleOutputCP(CP_UTF8);    // Set the console output code page to UTF-8

	system("cls");					// Render Clear
}

void ScreenClear()
{
	COORD coord = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(screenBuffer[screenIndex], ' ', 80 * 25, coord, &dw);
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(screenBuffer[screenIndex]);
	screenIndex = (screenIndex == 0) ? 1 : 0;
}

void ScreenRelease()
{
	CloseHandle(screenBuffer[0]);
	CloseHandle(screenBuffer[1]);
}

void ScreenPrint(int x, int y, char* string)
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
	cursorInfo.bVisible = 0;

	GetConsoleCursorInfo(screenBuffer[1], &cursorInfo);
	SetConsoleCursorInfo(screenBuffer[0], &cursorInfo);

	GetConsoleCursorInfo(screenBuffer[0], &cursorInfo);
	SetConsoleCursorInfo(screenBuffer[1], &cursorInfo);
}

void GotoCoordinate(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}