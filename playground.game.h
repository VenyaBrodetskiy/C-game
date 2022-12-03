#pragma once

char**	initPlayGroundMap(char** PlayGroundMap, RECT_ PlayGroundInBlocks);
char**	clearPlayGround	 (char** PlayGroundMap, RECT_ PlayGroundInPixels, BOOL isEnabledWalls);
RECT_	GetPlayGroundInBlocks(int widthBlock, int heightBlock);
RECT_	GetPlayGroundInPixels(RECT_ PlayGroundInBlocks, int pixelBlock);
void	freePlayGroundMap(char** PlayGroundMap, RECT_ PlayGroundInBlocks);
