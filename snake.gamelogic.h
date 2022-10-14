#pragma once
#include "framework.h"
#include "main.h"

int initSnake(HWND hWindowMain, RECT GameFieldRect);
int moveSnake(HWND hWindowMain, RECT GameFieldRect);
int changeSnakeDirection(WPARAM wParam);
int gameOver(HWND hWindowMain);