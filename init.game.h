#pragma once
#include "params.game.h"

// ASK ALON (how can I remove it from here, I need BOOl and RECT)
#include "windows.h"


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

int initPlayGround(RECT PlayGroundInPixels, BOOL isEnabledWalls);
int initSnake(RECT PlayGroundInPixels);
RECT GetPlayGroundInBlocks(int widthBlock, int heightBlock);
RECT GetPlayGroundInPixels(RECT PlayGroundInBlocks, int pixelBlock);
