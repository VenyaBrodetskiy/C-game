#include "snake.gamelogic.h"

extern Snake snake;
extern char PlayGroundMap[200][100];
extern RECT PlayGroundInBlocks;
extern RECT PlayGroundInPixels;
extern HDC hdc;

int initSnake(RECT GameField)
{
    // set speed and direction
    snake.speed = DEFAULT_SPEED;
    snake.direct = RIGHT;

    // init snake
    int center_x = (PlayGroundInBlocks.right - PlayGroundInBlocks.left) / 2;
    int center_y = (PlayGroundInBlocks.bottom - PlayGroundInBlocks.top) / 2;
    for (int index = 0; index < SNAKE_LENGHT; index++) 
    {
        snake.body[index].x = center_x - index;
        snake.body[index].y = center_y;
        PlayGroundMap[snake.body[index].x][snake.body[index].y] = SNAKE;
    }

    // find head and tail
    snake.indexOfHead = 0;
    snake.indexOfTail = SNAKE_LENGHT - 1;

    snake.head = snake.body[0];
    snake.tail = snake.body[SNAKE_LENGHT - 1];

    generateFood(PlayGroundInBlocks);

    return 1;
}

int changeSnakeDirection(WPARAM wParam)
{
    switch (wParam)
    {
    case VK_UP:
        if (snake.direct != DOWN) snake.direct = UP;
        break;
    case VK_DOWN:
        if (snake.direct != UP) snake.direct = DOWN;
        break;
    case VK_LEFT:
        if (snake.direct != RIGHT) snake.direct = LEFT;
        break;
    case VK_RIGHT:
        if (snake.direct != LEFT) snake.direct = RIGHT;
        break;
    }

    return 1;
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

    // check if head hit the wall / body / food / nothing
    switch (PlayGroundMap[snake.head.x][snake.head.y])
    {
    case WALL:
    case SNAKE:
    {
        KillTimer(hWindowMain, 2);
        paintSnake(hWindowMain, hdc, PlayGroundInPixels);
        MessageBoxW(NULL, L"Game is over", L"Game Over", MB_OK);
    }
        break;
    case FOOD:
    {
        snake.body[snake.indexOfTail + 1] = snake.tail;

        for (int index = snake.indexOfTail; index > snake.indexOfHead; index--)
        {
            snake.body[index] = snake.body[index - 1];
        }
        snake.body[0] = snake.head;
        PlayGroundMap[snake.head.x][snake.head.y] = SNAKE;

        // update tail
        snake.indexOfTail++;
        snake.tail = snake.body[snake.indexOfTail];
        generateFood(PlayGroundInBlocks);
    }
        break;
    case EMPTY:
    {
        PlayGroundMap[snake.tail.x][snake.tail.y] = EMPTY;
        for (int index = snake.indexOfTail; index > snake.indexOfHead; index--)
        {
            snake.body[index] = snake.body[index - 1];
        }
        snake.body[0] = snake.head;
        PlayGroundMap[snake.head.x][snake.head.y] = SNAKE;

        snake.tail = snake.body[snake.indexOfTail];
    }
        break;
    }

    return 1;
}