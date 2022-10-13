#include "game.paint.h"

extern RECT snake;

int paintGameField(HWND hWindowMain, HDC hdc)
{
    RECT ClientRect;

    GetClientRect(hWindowMain, &ClientRect);

    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Rectangle(hdc, ClientRect.left, ClientRect.top, ClientRect.right - BUTTON1_SIZE_X, ClientRect.bottom);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);

    DeleteObject(hPen);
    DeleteObject(hOldBrush);
}

int paintSnake(HWND hWindowMain, HDC hdc)
{
    paintGameField(hWindowMain, hdc);

    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 200));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Rectangle(hdc, snake.left, snake.top, snake.right, snake.bottom);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hOldBrush);

    return 1;
}