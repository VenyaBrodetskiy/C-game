#include "game.paint.h"

extern Snake snake;
extern RECT PlayGroundInBlocks;
extern char PlayGroundMap[200][100];
extern int counterBonus;

int paintGameField(HDC hdc, RECT PlayGroundInPixels)
{
    HBRUSH hBrush = CreateSolidBrush(COLOR_BLACK);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    HPEN hPen = CreatePen(PS_SOLID, 1, COLOR_BLACK);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Rectangle(hdc, PlayGroundInPixels.left, PlayGroundInPixels.top, PlayGroundInPixels.right, PlayGroundInPixels.bottom);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);

    DeleteObject(hPen);
    DeleteObject(hBrush);

    return 1;
}

int drawPlayGround(HWND hWindowMain, HDC hdc, RECT PlayGroundInPixels)
{
    // create buffer - to draw in memory
    HDC bufferDC = CreateCompatibleDC(hdc);
    HBITMAP bufferBitMap = CreateCompatibleBitmap(hdc,
        PlayGroundInPixels.right - PlayGroundInPixels.left, PlayGroundInPixels.bottom - PlayGroundInPixels.top);
    SelectObject(bufferDC, bufferBitMap);

    // from here we paint in buffer
    paintGameField(bufferDC, PlayGroundInPixels);

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
            {
                int green = 128 - counterBonus;
                int blue = green;
                COLORREF color_food = RGB(200, green, blue);
                paintRoundBlock(bufferDC, x, y, color_food, color_food);
                break;
            }
            }
            
        }
    }

    // copy from buffer to dc
    BitBlt(hdc, 0, 0, PlayGroundInPixels.right, PlayGroundInPixels.bottom,
        bufferDC, 0, 0, SRCCOPY);
    
    // delete buffer
    DeleteDC(bufferDC);
    DeleteObject(bufferBitMap);

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