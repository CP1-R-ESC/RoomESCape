#pragma once
#pragma warning(disable:4996)

#define BLACK	   0
#define BLUE1	   1
#define GREEN1	   2
#define CYAN1	   3
#define RED1	   4
#define MAGENTA1   5
#define YELLOW1    6
#define GRAY1	   7
#define GRAY2	   8
#define BLUE2	   9
#define GREEN2	  10
#define CYAN2	  11
#define RED2	  12
#define MAGENTA2  13
#define YELLOW2	  14
#define WHITE	  15

void ScreenInitialize();	// display buffer initialize - front buffer, back buffer create
void ScreenClear();			// one buffer draw, other buffer have to be cleared
void ScreenFlipping();		// active buffer change state
void ScreenRelease();		// release two buffer
void ScreenPrint(int x, int y, char* string);			// output

void SetColor(int fgColor, int bgColor);
void HideCursor();
void GotoCoordinate(int x, int y);