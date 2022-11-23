#pragma once

char** initPlayGround(char** PlayGroundMap, RECT_ PlayGroundInPixels, BOOL isEnabledWalls);
void initSnake(Snake* snake, char** PlayGroundMap, RECT_ PlayGroundInPixels);
RECT_ GetPlayGroundInBlocks(int widthBlock, int heightBlock);
RECT_ GetPlayGroundInPixels(RECT_ PlayGroundInBlocks, int pixelBlock);
