#pragma once

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

#define DEFAULT_SPEED 3

typedef struct
{
    RECT position;
    int speed;
    int speedX;
    int speedY;
} Snake;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
