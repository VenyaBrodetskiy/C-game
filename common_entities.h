#pragma once
#include "params.game.h"
#include "linked.list.h"

#include <tchar.h>

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

typedef int updateScore_t(int score);
typedef int getSnakeSpeed_t();
typedef void setButtonContinue_t();
typedef void setButtonPause_t();
typedef void createTimer_t(int timer, int speed);
typedef void stopTimer_t(int timer);
typedef void popUpGameOver_t(wchar_t message[]);

typedef struct _ControlUI
{
    updateScore_t* updateScore_f;
    getSnakeSpeed_t* getSnakeSpeed_f;
    setButtonContinue_t* setButtonContinue_f;
    setButtonPause_t* setButtonPause_f;
    createTimer_t* createTimer_f;
    stopTimer_t* stopTimer_f;
    popUpGameOver_t* popUpGameOver_f;
} ControlUI;

typedef struct Snake
{
    // properties
    enum Direct direct;
    list_t body;
    int speed;
    int bonusSpeed;
    int score;
    int foodBonus;
    BOOL isGameStarted;
    BOOL isGamePaused;
    // functions
    ControlUI* controlUI;
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
