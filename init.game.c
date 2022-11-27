#include "common_entities.h"
#include "init.game.h"
#include <math.h>
#include <stdlib.h>

#include "linked.list.h"
#include "private.list.h"

char** initPlayGround(char** PlayGroundMap, RECT_ PlayGroundInBlocks, BOOL isEnabledWalls)
{
	if (PlayGroundInBlocks.bottom <= 1 || PlayGroundInBlocks.right <= 1) return 0;

	free(PlayGroundMap);
	PlayGroundMap = (char**)malloc((PlayGroundInBlocks.right + 1) * sizeof(char*));
	if (PlayGroundMap != NULL)
	{
		for (int i = 0; i <= PlayGroundInBlocks.right; i++)
		{
			PlayGroundMap[i] = (char*)malloc((PlayGroundInBlocks.bottom + 1) * sizeof(char));
			if (PlayGroundMap[i] == NULL) return 0;
		}
	}
	
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

	// init snake
	int center_x = (PlayGroundInBlocks.right - PlayGroundInBlocks.left) / 2;
	int center_y = (PlayGroundInBlocks.bottom - PlayGroundInBlocks.top) / 2;
	
	//for (int index = 0; index < SNAKE_LENGHT; index++)
	//{
	//	if (index < sizeof(snake->body))
	//	{
	//		snake->body[index].x = center_x - index;
	//		snake->body[index].y = center_y;
	//		PlayGroundMap[snake->body[index].x][snake->body[index].y] = SNAKE;
	//	}
	//	
	//}
	//// find head and tail
	//snake->indexOfTail = SNAKE_LENGHT - 1;

	//snake->head = snake->body[0];
	//snake->tail = snake->body[snake->indexOfTail];

	// body with list
	snake->body_list = list_create();
	Point* body_node;
	for (int index = 0; index < SNAKE_LENGHT; index++)
	{
		body_node = malloc(sizeof(Point));
		// VENYA DON'T FORGET TO FREE MEMORY
		body_node->x = center_x - index;
		body_node->y = center_y;
		list_add_tail(snake->body_list, body_node);

		PlayGroundMap[body_node->x][body_node->y] = SNAKE;
	}
	
	list_ptr_t body_list = (list_ptr_t)(snake->body_list);
	snake->head = *(Point*)body_list->head_ptr->data_ptr;
	snake->tail = *(Point*)body_list->head_ptr->prev_ptr->data_ptr;
	snake->indexOfTail = SNAKE_LENGHT - 1;

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