#pragma once
#include "framework.h"
#include "main.h"

int initSnake(RECT PlayGroundInPixels);
int moveSnake(HWND hWindowMain);
int changeSnakeDirection(WPARAM wParam);
int gameOver(HWND hWindowMain);