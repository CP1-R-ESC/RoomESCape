#pragma once
#pragma warning(disable:4996)

#include <stdbool.h>

#define FRAME_BUFFER_SIZE 10

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

enum Color
{
    BLACK = 0,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VOILET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE = 15,
};


void InitializeScreen();						// display buffer initialize - front buffer, back buffer create
void RenderScreen();
void ClearScreen();								// one buffer draw, other buffer have to be cleared
void FlippingScreen();							// active buffer change state
void CheckFrameScreen();
void WaitRenderScreen(bool* isDownESC);
void ReleaseScreen();							// release two buffer
void PrintScreen(int x, int y, char* string);	// output

void SetColor(int fgColor, int bgColor);
void HideCursor();