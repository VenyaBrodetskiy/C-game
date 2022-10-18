#pragma once

#include "main.h"

// tips text params
#define BIG_TIPS_WIDTH 400
#define BIG_TIPS_HEIGHT 250

// Colors
#define COLOR_SNAKE RGB(128, 128, 255)
#define COLOR_WALL RGB(0, 0, 128)
#define COLOR_FOOD RGB(255, 128, 128)
#define COLOR_BLACK RGB(0, 0, 0)

int drawGameTips(HDC hdc, RECT PlayGroundInPixels);
int drawGameField(HDC hdc, RECT GameField);
int drawPlayGround(HWND hWindowMain, HDC hdc, RECT GameField);
int drawSquareBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen);
int drawRoundBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen);