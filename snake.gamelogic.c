#include "snake.gamelogic.h"

extern Snake snake;
extern char PlayGroundMap[200][100];
extern RECT PlayGroundInBlocks;
extern RECT PlayGroundInPixels;
extern HDC hdc;
extern HWND hDynamicText1;
extern BOOL isGameStarted;

BOOL changeSnakeDirection(WPARAM wParam, BOOL isKeyDown)
{
    switch (wParam)
    {
    case VK_UP:
        if (snake.direct != DOWN && !isKeyDown) 
        {
            snake.direct = UP;
            isKeyDown = TRUE;
        }
        break;
    case VK_DOWN:
        if (snake.direct != UP && !isKeyDown)
        {
            snake.direct = DOWN;
            isKeyDown = TRUE;
        }
        break;
    case VK_LEFT:
        if (snake.direct != RIGHT && !isKeyDown)
        {
            snake.direct = LEFT;
            isKeyDown = TRUE;
        }
        break;
    case VK_RIGHT:
        if (snake.direct != LEFT && !isKeyDown)
        {
            snake.direct = RIGHT;
            isKeyDown = TRUE;
        }
        break;
    }

    return isKeyDown;
}

int moveSnake(HWND hWindowMain)
{
    // count next step
    switch (snake.direct)
    {
    case RIGHT:
        snake.head.x++;
        break;
    case LEFT:
        snake.head.x--;
        break;
    case UP:
        snake.head.y--;
        break;
    case DOWN:
        snake.head.y++;
        break;
    }

    // check if head is within PlayGround
    if (snake.head.x < 0) snake.head.x = PlayGroundInBlocks.right - 1;
    if (snake.head.x > PlayGroundInBlocks.right - 1) snake.head.x = 0;
    if (snake.head.y < 0) snake.head.y = PlayGroundInBlocks.bottom - 1;
    if (snake.head.y > PlayGroundInBlocks.bottom - 1) snake.head.y = 0;

    // check if head hit the wall / body / food / nothing
    switch (PlayGroundMap[snake.head.x][snake.head.y])
    {
    case WALL:
    case SNAKE:
    {
        gameOver(hWindowMain);
    }
        break;
    case FOOD:
    {
        snake.score++;
        updateScore(hDynamicText1, snake.score);
        snake.indexOfTail++;

        generateFood(PlayGroundInBlocks);
    }
    // here no need break, as further actions are same as if there is no food
    case EMPTY:
    {
        PlayGroundMap[snake.tail.x][snake.tail.y] = EMPTY;
        for (int index = snake.indexOfTail; index > 0; index--)
        {
            snake.body[index] = snake.body[index - 1];
        }
        snake.body[0] = snake.head;
        snake.tail = snake.body[snake.indexOfTail];
        PlayGroundMap[snake.head.x][snake.head.y] = SNAKE;
    }
        break;
    }

    return 1;
}


int updateScore(HWND hDynamicText, int score)
{
    wchar_t buf[10];
    UINT buf_len = 10;

    StringCbPrintfW(buf, buf_len, L"%d", score);
    SetWindowTextW(hDynamicText, buf);

    return 1;
}

int gameOver(HWND hWindowMain)
{
    KillTimer(hWindowMain, GAME_TIMER);
    drawPlayGround(hWindowMain, hdc, PlayGroundInPixels);
    MessageBoxW(hWindowMain, L"Game is over", L"Game Over", MB_OK);
    isGameStarted = FALSE;

    return 1;
}