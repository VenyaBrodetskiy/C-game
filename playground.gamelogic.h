#pragma once
#include "framework.h"
#include "main.h"

int initPlayGround(RECT PlayGroundInPixels);
int initSnake(RECT PlayGroundInPixels);
RECT CreatePlayGround(int widthBlock, int heightBlock);
RECT GetPlayGroundInPixels(RECT PlayGroundInBlocks, int pixelBlock);
int generateFood(RECT PlayGroundInBlocks);
