#pragma once

#include <strsafe.h>
#include "resource.h"
#include "framework.h"

#include "snake.gamelogic.h"
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

#define DEFAULT_SPEED 3

typedef struct Snake
{
    RECT position;
    int speed;
    int speedX;
    int speedY;
} Snake, *pSnake;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
