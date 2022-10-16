#pragma once
#include "framework.h"
#include "main.h"


int moveSnake(HWND hWindowMain);
BOOL changeSnakeDirection(WPARAM wParam, BOOL isKeyDown);
int updateScore(HWND hDynamicText, int score);
int gameOver(HWND hWindowMain, int score);
int generateFood(RECT PlayGroundInBlocks, HWND hWindowMain);
