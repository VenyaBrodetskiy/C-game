#pragma once
#include "main.h"

// game results
#define LOW_RESULT 40
#define AVERAGE_RESULT 200
#define HIGH_RESULT 500

int moveSnake(HWND hWindowMain);
BOOL changeSnakeDirection(WPARAM wParam, BOOL isKeyDown);
int gameOver(HWND hWindowMain, int score);
int generateFood(RECT PlayGroundInBlocks, HWND hWindowMain);
