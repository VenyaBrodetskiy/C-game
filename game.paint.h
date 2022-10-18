#pragma once

#include "framework.h"
#include "main.h"

int drawGameTips(HDC hdc, RECT PlayGroundInPixels);
int drawGameField(HDC hdc, RECT GameField);
int drawPlayGround(HWND hWindowMain, HDC hdc, RECT GameField);
int drawSquareBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen);
int drawRoundBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen);