#pragma once

#include "resource.h"
#include "framework.h"
#include <commctrl.h>
#include <strsafe.h>
#pragma comment(lib, "comctl32")


#include "snake.gamelogic.h"
#include "init.gamelogic.h"
#include "init.interface.h"
#include "update.interface.h"
#include "game.paint.h"
#include "game.paint.h"

#define MAX_LOADSTRING 100

// button start sizes
#define BUTTON_SIZE_X 100
#define BUTTON_SIZE_Y 35

// static text sizes
#define STAT_TEXT1_X 55
#define STAT_TEXT1_Y 25

// dynamic text sizes
#define DYN_TEXT1_X 45
#define DYN_TEXT1_Y STAT_TEXT1_Y

// tips text params
#define TIPS_WIDTH 400
#define TIPS_HEIGHT 250

// game params
#define SNAKE_LENGHT 5

// game interface params
#define PIXEL_BLOCK 20
#define FIELD_WIDTH 60
#define FIELD_HEIGHT 35

// game results
#define LOW_RESULT 40
#define AVERAGE_RESULT 200
#define HIGH_RESULT 500

// Colors
#define COLOR_SNAKE RGB(128, 128, 255)
#define COLOR_WALL RGB(0, 0, 128)
#define COLOR_FOOD RGB(255, 128, 128)
#define COLOR_BLACK RGB(0, 0, 0)

enum Buttons {
    BUTTON_START,
    BUTTON_PAUSE,
    STATIC_TEXT1,
    DYNAMIC_TEXT1,
    GROUP_BOX1,
    RADIO_WALLS,
    RADIO_NOWALLS,
    SPEED_LABEL,
    TRACK_BAR,
    STATIC_TEXT2,
    STATIC_TEXT3,
    PROGRESS_BAR
};

enum Timers {
    GAME_TIMER,
    FOOD_TIMER
};

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
    enum Direct direct;
    Point *body;
    Point head;
    Point tail;
    int indexOfTail;
    int speed;
    int score;
} Snake;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL startNewGame(HWND hWindowMain);