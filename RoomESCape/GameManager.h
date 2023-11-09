#pragma once
#pragma warning(disable:4996)

#define FALSE 0
#define TRUE  1

#define KEY_ESC	  27

void InitializeGame();
void UpdateGame();
void RenderGame();
void WaitGame(clock_t oldTime);
void ReleaseGame();

void GetKeyInput();