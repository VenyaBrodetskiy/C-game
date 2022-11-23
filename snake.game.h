#pragma once
#include <windows.h>

// game results
#define LOW_RESULT 40
#define AVERAGE_RESULT 200
#define HIGH_RESULT 500

void moveSnake(Snake* snake);
BOOL changeSnakeDirection(WPARAM wParam, Snake* snake, BOOL isKeyDown);
void gameOver(int score);
int generateFood(Snake* snake, RECT_ PlayGroundInBlocks);
BOOL startNewGame(Snake* snake, BOOL isEnabledWalls);
BOOL resumeGame(Snake* snake);
BOOL pauseGame();
