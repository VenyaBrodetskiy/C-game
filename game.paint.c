#include <windows.h>
#include "game.paint.h"
#include "init.game.h"
#include "params.game.h"

extern Snake snake;
extern RECT PlayGroundInBlocks;
extern char **PlayGroundMap;
extern int foodBonus;

int drawGameTips(HDC hdc, RECT PlayGroundInPixels)
{
    HWND hFont1 = CreateFontW(20, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Consolas");
    HWND hOldFont = SelectObject(hdc, hFont1);
    SetTextColor(hdc, COLOR_SNAKE);
    SetBkColor(hdc, COLOR_BLACK);

    RECT textRect =
    {
        (PlayGroundInPixels.right - BIG_TIPS_WIDTH) / 2,
        (PlayGroundInPixels.bottom - BIG_TIPS_HEIGHT) / 2,
        (PlayGroundInPixels.right + BIG_TIPS_WIDTH) / 2,
        (PlayGroundInPixels.bottom + BIG_TIPS_HEIGHT) / 2
    };

    DrawTextW(hdc,
        L"Welcome!\n"
        L"\n"
        L"This is NOKIA inspired snake!\n\n"
        L"Before you start, please choose game mode and speed.\n"
        L"\n"
        L"Tips:\n"
        L"- Use Arrow Keys to control snake\n"
        L"- Press Enter to start the game\n"
        L"- Press Space to pause\n"
        L"- Mind the Bonus",
        206, &textRect, DT_WORDBREAK);
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont1);

    return 1;
}

int drawGameField(HDC hdc, RECT PlayGroundInPixels)
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

int drawPlayGround(HDC hdc, RECT PlayGroundInPixels)
{
    // create buffer - to draw in memory
    HDC bufferDC = CreateCompatibleDC(hdc);
    HBITMAP bufferBitMap = CreateCompatibleBitmap(hdc,
        PlayGroundInPixels.right - PlayGroundInPixels.left, PlayGroundInPixels.bottom - PlayGroundInPixels.top);
    SelectObject(bufferDC, bufferBitMap);

    // from here we paint in buffer
    drawGameField(bufferDC, PlayGroundInPixels);

    for (int x = 0; x <= PlayGroundInBlocks.right; x++) 
    {
        for (int y = 0; y <= PlayGroundInBlocks.bottom; y++)
        {
            switch (PlayGroundMap[x][y])
            {
            case SNAKE:
                if (snake.head.x == x && snake.head.y == y) drawSquareBlock(bufferDC, x, y, COLOR_SNAKE, COLOR_SNAKE);
                else drawSquareBlock(bufferDC, x, y, COLOR_SNAKE, RGB(0, 0, 100));
                break;
            case WALL:
                drawSquareBlock(bufferDC, x, y, COLOR_WALL, COLOR_WALL);
                break;
            case FOOD:
            {
                int green = 128 - foodBonus;
                int blue = green;
                COLORREF color_food = RGB(200, green, blue);
                drawRoundBlock(bufferDC, x, y, color_food, color_food);
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

int drawSquareBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen) 
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

int drawRoundBlock(HDC dc, int x, int y, COLORREF brush, COLORREF pen)
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