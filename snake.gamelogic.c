#include "snake.gamelogic.h"
extern Snake snake;

int initSnake(HWND hWindowMain, RECT GameFieldRect)
{
    snake.speed = DEFAULT_SPEED;
    snake.speedX = 0;
    snake.speedY = 0;
    snake.position.left = (GameFieldRect.right - GameFieldRect.left) / 2;
    snake.position.right = snake.position.left + 50;
    snake.position.top = (GameFieldRect.bottom - GameFieldRect.top) / 2;
    snake.position.bottom = snake.position.top + 10;

    snake.speedX = snake.speed;

    return 1;
}

int moveSnake(HWND hWindowMain, RECT GameFieldRect)
{
    if (snake.position.right >= GameFieldRect.right - snake.speedX)
    {
        snake.speedX = -snake.speedX;
    }
    if (snake.position.left <= GameFieldRect.left - snake.speedX)
    {
        snake.speedX = -snake.speedX;
    }
    if (snake.position.top <= GameFieldRect.top - snake.speedY)
    {
        snake.speedY = -snake.speedY;
    }
    if (snake.position.bottom >= GameFieldRect.bottom - snake.speedY)
    {
        snake.speedY = -snake.speedY;
    }

    snake.position.left += snake.speedX;
    snake.position.right += snake.speedX;


    snake.position.top += snake.speedY;
    snake.position.bottom += snake.speedY;

    return 1;
}

int changeSnakeDirection(WPARAM wParam)
{
    switch (wParam)
    {
    case VK_UP:
        snake.speedY = -snake.speed;
        snake.speedX = 0;
        break;
    case VK_DOWN:
        snake.speedY = snake.speed;
        snake.speedX = 0;
        break;
    case VK_LEFT:
        snake.speedY = 0;
        snake.speedX = -snake.speed;
        break;
    case VK_RIGHT:
        snake.speedY = 0;
        snake.speedX = snake.speed;
        break;
    }
}