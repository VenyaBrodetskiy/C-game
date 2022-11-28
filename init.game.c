#include "common_entities.h"
#include "init.game.h"
#include <math.h>
#include <stdlib.h>

#include "linked.list.h"

char** initPlayGroundMap(char** PlayGroundMap, RECT_ PlayGroundInBlocks)
{
	if (PlayGroundInBlocks.bottom <= 1 || PlayGroundInBlocks.right <= 1) return 0;

	PlayGroundMap = (char**)malloc((PlayGroundInBlocks.right + 1) * sizeof(char*));
	if (PlayGroundMap != NULL)
	{
		for (int i = 0; i <= PlayGroundInBlocks.right; i++)
		{
			PlayGroundMap[i] = (char*)malloc((PlayGroundInBlocks.bottom + 1) * sizeof(char));
			if (PlayGroundMap[i] == NULL) return 0;
		}
	}

	return PlayGroundMap;
}

char** clearPlayGround(char** PlayGroundMap, RECT_ PlayGroundInBlocks, BOOL isEnabledWalls)
{
	// clear PlayGround
	if (PlayGroundMap != NULL && PlayGroundMap[0] != NULL) // check if memory was allocated
	{
		for (int x = 0; x <= PlayGroundInBlocks.right; x++) {
			for (int y = 0; y <= PlayGroundInBlocks.bottom; y++) {
				PlayGroundMap[x][y] = EMPTY;
			}
		}
		// build walls
		if (isEnabledWalls == 1)
		{
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
		}
	}

	return PlayGroundMap;
}

void initSnake(Snake* snake, char** PlayGroundMap, RECT_ PlayGroundInBlocks)
{
	// clear points
	snake->score = 0;
	updateScore(snake->score);
	snake->foodBonus = MAX_BONUS;

	// set direction and speed
	snake->direct = RIGHT;
	snake->speed = getSnakeSpeed();
	snake->bonusSpeed = (int)round(snake->speed / BONUS_COEFF) + SPEED_MAX;

	// clear game status variables
	snake->isGameStarted = TRUE;
	snake->isGamePaused = FALSE;

	// free memory from previous snake
	if (snake->body != NULL)
	{
		list_destroy(snake->body, free);
		// STILL MEMORY DRAINS 
		// ASK ALON
	}
	// init snake
	snake->body = list_create();

	int center_x = (PlayGroundInBlocks.right - PlayGroundInBlocks.left) / 2;
	int center_y = (PlayGroundInBlocks.bottom - PlayGroundInBlocks.top) / 2;

	for (int index = 0; index < SNAKE_LENGHT; index++)
	{
		Point* body_node = malloc(sizeof(Point));

		body_node->x = center_x - index;
		body_node->y = center_y;
		list_add_tail(snake->body, body_node);

		PlayGroundMap[body_node->x][body_node->y] = SNAKE;
	}
}

RECT_ GetPlayGroundInBlocks(int widthBlock, int heightBlock)
{
	RECT_ PlayGroundInBlocks = { 0 };
	PlayGroundInBlocks.left = 0; // if some bug happens, change to 1
	PlayGroundInBlocks.top = 0; // if some bug happens, change to 1
	PlayGroundInBlocks.bottom = heightBlock;
	PlayGroundInBlocks.right = widthBlock;

	return PlayGroundInBlocks;
}

RECT_ GetPlayGroundInPixels(RECT_ PlayGroundInBlocks, int pixelBlock)
{
	RECT_ PlayGroundInPixels = { 0 };
	PlayGroundInPixels.left = 0;
	PlayGroundInPixels.top = 0;
	PlayGroundInPixels.right = PlayGroundInBlocks.right * pixelBlock;
	PlayGroundInPixels.bottom = PlayGroundInBlocks.bottom * pixelBlock;

	return PlayGroundInPixels;
}

void freePlayGroundMap(char** PlayGroundMap, RECT_ PlayGroundInBlocks)
{
	for (int i = 0; i <= PlayGroundInBlocks.right; i++)
	{
		free(PlayGroundMap[i]);
	}
	free(PlayGroundMap);
}