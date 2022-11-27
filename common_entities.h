#pragma once
#include "params.game.h"
#include "linked.list.h"

#ifndef GAME_FOR_WIN_API
#define GAME_FOR_WIN_API
#endif // !GAME_FOR_WIN_API


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef long LONG;
typedef int BOOL;

typedef struct
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT_, * PRECT_;

enum Field {
    EMPTY,
    SNAKE,
    WALL,
    FOOD
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
    list_t body_list;
    Point head;
    Point tail;
    int indexOfTail;
    int speed;
    int bonusSpeed;
    int score;
    int foodBonus;
    BOOL isGameStarted;
    BOOL isGamePaused;
} Snake;

enum Direct {
    RIGHT,
    LEFT,
    UP,
    DOWN
};

typedef enum Timers {
    GAME_TIMER,
    FOOD_TIMER
} Timers;

typedef void* KEYDOWN;