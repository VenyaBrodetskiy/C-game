#include "init.gamelogic.h"

extern char PlayGroundMap[200][100];
extern Snake snake;
extern HWND hTrackBar, hDynamicText1;

int initPlayGround(RECT PlayGroundInBlocks, BOOL isEnabledWalls)
{
	if (PlayGroundInBlocks.bottom <= 1 || PlayGroundInBlocks.right <= 1) return 0;
	
	// clear 
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

	return 1;
}

int initSnake(RECT PlayGroundInBlocks, HWND hWindowMain)
{
	// clear points
	snake.score = 0;
	updateScore(hDynamicText1, snake.score);

	// set direction and speed
	snake.direct = RIGHT;
	snake.speed = SendMessageW(hTrackBar, TBM_GETPOS, 0, 0);

	// init snake
	int center_x = (PlayGroundInBlocks.right - PlayGroundInBlocks.left) / 2;
	int center_y = (PlayGroundInBlocks.bottom - PlayGroundInBlocks.top) / 2;
	for (int index = 0; index < SNAKE_LENGHT; index++)
	{
		snake.body[index].x = center_x - index;
		snake.body[index].y = center_y;
		PlayGroundMap[snake.body[index].x][snake.body[index].y] = SNAKE;
	}

	// find head and tail
	snake.indexOfTail = SNAKE_LENGHT - 1;

	snake.head = snake.body[0];
	snake.tail = snake.body[SNAKE_LENGHT - 1];

	generateFood(PlayGroundInBlocks, hWindowMain);

	return 1;
}

RECT CreatePlayGround(int widthBlock, int heightBlock)
{
	RECT PlayGroundInBlocks;
	PlayGroundInBlocks.left = 1;
	PlayGroundInBlocks.top = 1;
	PlayGroundInBlocks.bottom = heightBlock;
	PlayGroundInBlocks.right = widthBlock;

	return PlayGroundInBlocks;
}

RECT GetPlayGroundInPixels(RECT PlayGroundInBlocks, int pixelBlock)
{
	RECT PlayGroundInPixels;
	PlayGroundInPixels.left = 0;
	PlayGroundInPixels.top = 0;
	PlayGroundInPixels.right = PlayGroundInBlocks.right * pixelBlock;
	PlayGroundInPixels.bottom = PlayGroundInBlocks.bottom * pixelBlock;

	return PlayGroundInPixels;
}