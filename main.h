#pragma once

#include "resource.h"
#include "framework.h"
#include <commctrl.h>
#include <strsafe.h>
#pragma comment(lib, "comctl32")

#include "params.game.h"
#include "snake.game.h"
#include "init.game.h"
#include "params.interface.h"
#include "init.interface.h"
#include "update.interface.h"
#include "game.paint.h"
#include "game.paint.h"

#define MAX_LOADSTRING 100

typedef enum Timers {
    GAME_TIMER,
    FOOD_TIMER
} Timers;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL startNewGame(HWND hWindowMain);
BOOL resumeGame(HWND hWindowMain);
BOOL pauseGame(HWND hWindowMain);