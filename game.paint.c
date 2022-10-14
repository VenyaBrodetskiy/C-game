#include "game.paint.h"

extern Snake snake;
extern RECT PlayGroundInBlocks;
extern char PlayGroundMap[200][100];

int paintGameField(HDC hdc, RECT PlayGroundInPixels)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    HPEN hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 200));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Rectangle(hdc, PlayGroundInPixels.left, PlayGroundInPixels.top, PlayGroundInPixels.right, PlayGroundInPixels.bottom);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);

    DeleteObject(hPen);
    DeleteObject(hOldBrush);

    return 1;
}

int drawPlayGround(HWND hWindowMain, HDC hdc, RECT PlayGroundInPixels)
{
    // create buffer - to draw in memory
    HDC bufferDC = CreateCompatibleDC(hdc);
    HBITMAP bufferBitMap = CreateCompatibleBitmap(hdc,
        PlayGroundInPixels.right - PlayGroundInPixels.left, PlayGroundInPixels.bottom - PlayGroundInPixels.top);
    SelectObject(bufferDC, bufferBitMap);

    // now we paint in buffer
    paintGameField(bufferDC, PlayGroundInPixels);

    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 200));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(bufferDC, hBrush);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HPEN hOldPen = (HPEN)SelectObject(bufferDC, hPen);

    for (int x = 0; x <= PlayGroundInBlocks.right; x++) 
    {
        for (int y = 0; y <= PlayGroundInBlocks.bottom; y++)
        {
            switch (PlayGroundMap[x][y])
            {
            case SNAKE:
                if (snake.head.x == x && snake.head.y == y) paintSquareBlock(bufferDC, x, y, COLOR_SNAKE, COLOR_SNAKE);
                else paintSquareBlock(bufferDC, x, y, COLOR_SNAKE, RGB(0, 0, 100));
                break;
            case WALL:
                paintSquareBlock(bufferDC, x, y, COLOR_WALL, COLOR_WALL);
                break;
            case FOOD:
                paintRoundBlock(bufferDC, x, y, COLOR_FOOD, COLOR_FOOD);
                break;
            }
            
        }
    }

    // copy from buffer to dc
    BitBlt(hdc, 0, 0, PlayGroundInPixels.right, PlayGroundInPixels.bottom,
        bufferDC, 0, 0, SRCCOPY);
    // delete buffer
    DeleteDC(bufferDC);
    DeleteObject(bufferBitMap);

    SelectObject(bufferDC, hOldPen);
    SelectObject(bufferDC, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);

    return 1;
}

int paintSquareBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen) 
{
    HBRUSH hBrush = CreateSolidBrush(brush);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(dc, hBrush);
    HPEN hPen = CreatePen(PS_SOLID, 1, pen);
    HPEN hOldPen = (HPEN)SelectObject(dc, hPen);

    Rectangle(dc,
        x * PIXEL_BLOCK, y * PIXEL_BLOCK,
        x * PIXEL_BLOCK + PIXEL_BLOCK, y * PIXEL_BLOCK + PIXEL_BLOCK);

    SelectObject(dc, hOldPen);
    SelectObject(dc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);

    return 1;
}

int paintRoundBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen)
{
    HBRUSH hBrush = CreateSolidBrush(brush);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(dc, hBrush);
    HPEN hPen = CreatePen(PS_SOLID, 1, pen);
    HPEN hOldPen = (HPEN)SelectObject(dc, hPen);

    Ellipse(dc,
        x * PIXEL_BLOCK, y * PIXEL_BLOCK,
        x * PIXEL_BLOCK + PIXEL_BLOCK, y * PIXEL_BLOCK + PIXEL_BLOCK);

    SelectObject(dc, hOldPen);
    SelectObject(dc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);

    return 1;
}