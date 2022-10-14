#pragma once

#include "framework.h"
#include "main.h"

int paintGameField(HDC hdc, RECT GameField);
int drawPlayGround(HWND hWindowMain, HDC hdc, RECT GameField);
int paintSquareBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen);
int paintRoundBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen);