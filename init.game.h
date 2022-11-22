#pragma once
#include "params.game.h"
#include <windows.h>

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

// ask Alon how to make it work
//typedef long LONG;
//typedef int BOOL;
//
//typedef struct
//{
//    LONG    left;
//    LONG    top;
//    LONG    right;
//    LONG    bottom;
//} RECT, * PRECT;

int initPlayGround(RECT PlayGroundInPixels, BOOL isEnabledWalls);
int initSnake(RECT PlayGroundInPixels);
RECT GetPlayGroundInBlocks(int widthBlock, int heightBlock);
RECT GetPlayGroundInPixels(RECT PlayGroundInBlocks, int pixelBlock);
