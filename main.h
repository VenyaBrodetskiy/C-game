#pragma once

#include <strsafe.h>
#include "resource.h"
#include "framework.h"

#include "snake.gamelogic.h"
#include "playground.gamelogic.h"
#include "init.interface.h"
#include "update.interface.h"
#include "game.paint.h"
#include "game.paint.h"

#define MAX_LOADSTRING 100
#define ID_HOTKEY_1 1 // for hot key Ctrl + C
#define C_BUTTON 0x43 // code of "C" from keyboard

#define BUTTON_START 3 // N of button
#define BUTTON1_SIZE_X 100
#define BUTTON1_SIZE_Y 30

// static text parameters
#define STAT_TEXT1_X 55
#define STAT_TEXT1_Y 25

// dynamic text parameters
#define DYN_TEXT1_X 45
#define DYN_TEXT1_Y STAT_TEXT1_Y

// game params
#define DEFAULT_SPEED 3
#define SNAKE_LENGHT 2

//
#define PIXEL_BLOCK 20
#define PG_BORDER PIXEL_BLOCK
#define FIELD_WIDTH 60
#define FIELD_HEIGHT 35

// Colors
#define COLOR_SNAKE RGB(0, 0, 200)


typedef struct Point
{
    int x;
    int y;
} Point;

enum Direct {
    RIGHT,
    LEFT,
    UP,
    DOWN
};

enum Field {
    EMPTY,
    SNAKE,
    WALL,
    FOOD
};

typedef struct Snake
{
    int speed;
    enum Direct direct;
    Point body[1000];
    int indexOfHead;
    int indexOfTail;
    Point head;
    Point tail;
} Snake, *pSnake;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int counterIncrease();