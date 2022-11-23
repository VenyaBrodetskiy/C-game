#pragma once
#include <windows.h>

// game results
#define LOW_RESULT 40
#define AVERAGE_RESULT 200
#define HIGH_RESULT 500

int moveSnake();
BOOL changeSnakeDirection(WPARAM wParam, BOOL isKeyDown);
void gameOver(int score);
int generateFood(RECT_ PlayGroundInBlocks);
BOOL startNewGame(BOOL isEnabledWalls);
BOOL resumeGame();
BOOL pauseGame();
