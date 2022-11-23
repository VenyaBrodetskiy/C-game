#pragma once
#include "params.game.h"
#include "common_entities.h"

enum Field {
    EMPTY,
    SNAKE,
    WALL,
    FOOD
};

enum Direct {
    RIGHT,
    LEFT,
    UP,
    DOWN
};

typedef struct Point
{
    int x;
    int y;
} Point;

typedef struct Snake
{
    enum Direct direct;
    Point body[SNAKE_MAX_LENGTH];
    Point head;
    Point tail;
    int indexOfTail;
    int speed;
    int bonusSpeed;
    int score;
} Snake;

typedef enum Timers {
    GAME_TIMER,
    FOOD_TIMER
} Timers;


char** initPlayGround(char** PlayGroundMap, RECT_ PlayGroundInPixels, BOOL isEnabledWalls);
void initSnake(Snake* snake, char** PlayGroundMap, RECT_ PlayGroundInPixels);
RECT_ GetPlayGroundInBlocks(int widthBlock, int heightBlock);
RECT_ GetPlayGroundInPixels(RECT_ PlayGroundInBlocks, int pixelBlock);
