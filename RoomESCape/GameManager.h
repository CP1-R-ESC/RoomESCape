#pragma once
#pragma warning(disable:4996)

#include <time.h>
#include <stdbool.h>

#include "JsonManager.h"

#define FALSE 0
#define TRUE  1

#define KEY_ESC	  27

extern char* url;
extern char* jsonData;
extern Corporation* corporation;
extern int turn;
extern int maxTurn;

extern bool hasExitRenderThread;
extern bool hasLoadComplete;
extern bool isDownESC;

extern clock_t sharedCurTime, sharedOldTime;

bool InitializeGame();
void UpdateGame();
bool ProcessGame();
void WaitGame();
void ReleaseGame();

int GetKeyInput();