#include "snake.gamelogic.h"

extern Snake snake;
extern char FieldMap[1920][1080];

int initSnake(HWND hWindowMain, RECT GameField)
{
    // set speed and direction
    snake.speed = DEFAULT_SPEED;
    snake.direct = RIGHT;

    // init snake
    int center_x = (GameField.right - GameField.left) / 2;
    int center_y = (GameField.bottom - GameField.top) / 2;
    for (int index = 0; index < SNAKE_LENGHT; index++) 
    {
        snake.body[index].x = center_x - index;
        snake.body[index].y = center_y;
        FieldMap[snake.body[index].x][snake.body[index].y] = SNAKE;
    }

    // find head and tail
    snake.indexOfHead = 0;
    snake.indexOfTail = SNAKE_LENGHT - 1;

    return 1;
}

int moveSnake(HWND hWindowMain, RECT GameField)
{
    FieldMap[snake.body[snake.indexOfTail].x][snake.body[snake.indexOfTail].y] = EMPTY;
    for (int index = snake.indexOfTail; index > snake.indexOfHead; index--)
    {
        snake.body[index].x = snake.body[index - 1].x;
        snake.body[index].y = snake.body[index - 1].y;
    }
    if (snake.direct == RIGHT) 
    {
        snake.body[snake.indexOfHead].x = snake.body[snake.indexOfHead + 1].x + 1;
        snake.body[snake.indexOfHead].y = snake.body[snake.indexOfHead + 1].y;
    }
    if (snake.direct == LEFT)
    {
        snake.body[snake.indexOfHead].x = snake.body[snake.indexOfHead + 1].x - 1;
        snake.body[snake.indexOfHead].y = snake.body[snake.indexOfHead + 1].y;
    }
    if (snake.direct == UP)
    {
        snake.body[snake.indexOfHead].x = snake.body[snake.indexOfHead + 1].x;
        snake.body[snake.indexOfHead].y = snake.body[snake.indexOfHead + 1].y - 1;
    }
    if (snake.direct == DOWN)
    {
        snake.body[snake.indexOfHead].x = snake.body[snake.indexOfHead + 1].x;
        snake.body[snake.indexOfHead].y = snake.body[snake.indexOfHead + 1].y + 1;
    }
    if (FieldMap[snake.body[snake.indexOfHead].x][snake.body[snake.indexOfHead].y] == SNAKE ||
        FieldMap[snake.body[snake.indexOfHead].x][snake.body[snake.indexOfHead].y] == WALL)
    {
        gameOver(hWindowMain);
    }
    else 
    {
        FieldMap[snake.body[snake.indexOfHead].x][snake.body[snake.indexOfHead].y] = SNAKE;
    }
 
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
}

int gameOver(HWND hWindowMain)
{
    KillTimer(hWindowMain, 2);
    MessageBoxW(NULL, L"Game is over", L"Game Over", MB_OK);

}