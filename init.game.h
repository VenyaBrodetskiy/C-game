#pragma once
#include "main.h"

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
int initSnake(RECT PlayGroundInPixels, HWND hWindowMain);
RECT GetPlayGroundInBlocks(int widthBlock, int heightBlock);
RECT GetPlayGroundInPixels(RECT PlayGroundInBlocks, int pixelBlock);
