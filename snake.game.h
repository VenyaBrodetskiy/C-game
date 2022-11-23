#pragma once
#include <windows.h>

// game results
#define LOW_RESULT 40
#define AVERAGE_RESULT 200
#define HIGH_RESULT 500

void	moveSnake(Snake* snake, char** PlayGroundMap, RECT_ PlayGroundInBlocks);
BOOL	changeSnakeDirection(WPARAM wParam, Snake* snake, BOOL isKeyDown);
void	gameOver(Snake* snake);
int		generateFood(Snake* snake, char** PlayGroundMap, RECT_ PlayGroundInBlocks);
char**	startNewGame(Snake* snake, char** PlayGroundMap, RECT_ PlayGroundInBlocks, BOOL isEnabledWalls);
void	resumeGame(Snake* snake);
void	pauseGame(Snake* snake);
