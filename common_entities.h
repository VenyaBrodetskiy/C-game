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

// snake with linked list
typedef struct Snake
{
    enum Direct direct;
    list_t body;
    int speed;
    int bonusSpeed;
    int score;
    int foodBonus;
    BOOL isGameStarted;
    BOOL isGamePaused;
} Snake;

typedef struct _node_t
{
    void* data_ptr;
    struct _node_t* next_ptr;
    struct _node_t* prev_ptr;
} *node_ptr_t;

typedef struct _list_t
{
    node_ptr_t head_ptr;
    int size;
} *list_ptr_t;

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

typedef unsigned long long* KEYDOWN;
