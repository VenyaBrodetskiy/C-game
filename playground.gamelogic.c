#include "playground.gamelogic.h"

extern char PlayGroundMap[200][100];

int initPlayGround(RECT PlayGroundInBlocks) 
{
	// clear 
	for (int x = 0; x <= PlayGroundInBlocks.right; x++) {
		for (int y = 0; y <= PlayGroundInBlocks.bottom; y++) {
			PlayGroundMap[x][y] = EMPTY;
		}
	}

	// build walls
	for (int x = 0; x <= PlayGroundInBlocks.right; x++) {
		PlayGroundMap[x][0] = WALL;
	}
	for (int x = 0; x <= PlayGroundInBlocks.right; x++) {
		PlayGroundMap[x][PlayGroundInBlocks.bottom - 1] = WALL;
	}
	for (int y = 0; y <= PlayGroundInBlocks.bottom; y++) {
		PlayGroundMap[0][y] = WALL;
	}
	for (int y = 0; y <= PlayGroundInBlocks.bottom; y++) {
		PlayGroundMap[PlayGroundInBlocks.right - 1][y] = WALL;
	}

	return 1;
}

int generateFood(RECT PlayGroundInBlocks)
{
	// need to try make it function async
	Point food = { 0 };
	do
	{
		int a = rand();
		food.x = rand() * PlayGroundInBlocks.right / RAND_MAX;
		food.y = rand() * PlayGroundInBlocks.bottom / RAND_MAX;
	} while (PlayGroundMap[food.x][food.y] != EMPTY);

	PlayGroundMap[food.x][food.y] = FOOD;

	return 1;
}