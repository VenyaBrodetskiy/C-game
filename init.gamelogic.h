#pragma once
#include "framework.h"
#include "main.h"

int initPlayGround(RECT PlayGroundInPixels, BOOL isEnabledWalls);
int initSnake(RECT PlayGroundInPixels, HWND hWindowMain);
RECT CreatePlayGround(int widthBlock, int heightBlock);
RECT GetPlayGroundInPixels(RECT PlayGroundInBlocks, int pixelBlock);
