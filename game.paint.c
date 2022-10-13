#include "game.paint.h"

extern Snake snake;

int paintGameField(HDC hdc, RECT GameField)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Rectangle(hdc, GameField.left, GameField.top, GameField.right, GameField.bottom);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);

    DeleteObject(hPen);
    DeleteObject(hOldBrush);
}

int paintSnake(HWND hWindowMain, HDC hdc, RECT GameField)
{
    // create buffer - to draw in memory
    HDC bufferDC = CreateCompatibleDC(hdc);
    HBITMAP bufferBitMap = CreateCompatibleBitmap(hdc,
        GameField.right - GameField.left, GameField.bottom - GameField.top);
    SelectObject(bufferDC, bufferBitMap);

    // now we paint in buffer
    paintGameField(bufferDC, GameField);

    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 200));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(bufferDC, hBrush);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HPEN hOldPen = (HPEN)SelectObject(bufferDC, hPen);
    Rectangle(bufferDC, snake.position.left, snake.position.top, snake.position.right, snake.position.bottom);

    // copy from buffer to dc
    BitBlt(hdc, GameField.left, GameField.top, GameField.right, GameField.bottom,
        bufferDC, 0, 0, SRCCOPY);
    // delete buffer
    DeleteDC(bufferDC);
    DeleteObject(bufferBitMap);

    SelectObject(bufferDC, hOldPen);
    SelectObject(bufferDC, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hOldBrush);

    return 1;
}