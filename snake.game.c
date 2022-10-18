#include "snake.game.h"

extern Snake snake;
extern char **PlayGroundMap;
extern RECT PlayGroundInBlocks, PlayGroundInPixels;
extern HWND hDynamicText;
extern BOOL isGameStarted;
extern int foodBonus;

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
        gameOver(hWindowMain, snake.score);
    }
        break;
    case FOOD:
    {
        snake.indexOfTail++;

        snake.score = snake.score + SCORE_INCREMENT + foodBonus;
        updateScore(hDynamicText, snake.score);

        KillTimer(hWindowMain, FOOD_TIMER);
        generateFood(PlayGroundInBlocks, hWindowMain);
    }
    // here no need break, as further actions are same as if there is no food
    case EMPTY:
    {
        PlayGroundMap[snake.tail.x][snake.tail.y] = EMPTY; // snake growth on next move after eating food 
        PlayGroundMap[snake.head.x][snake.head.y] = SNAKE;

        for (int index = snake.indexOfTail; index > 0; index--)
        {
            snake.body[index] = snake.body[index - 1];
        }
        snake.body[0] = snake.head;
        snake.tail = snake.body[snake.indexOfTail];
    }
        break;
    }

    return 1;
}

int gameOver(HWND hWindowMain, int score)
{
    KillTimer(hWindowMain, GAME_TIMER);
    KillTimer(hWindowMain, FOOD_TIMER);
    isGameStarted = FALSE;

    wchar_t message[120];
    if (score < LOW_RESULT) 
        swprintf_s(message, 120, L"Your score: %d \nTry to adjust settings \n\nPress Enter to try again", score);
    else if (score < AVERAGE_RESULT) 
        swprintf_s(message, 120, L"Your score: %d \nכל הכבוד \n\nPress Enter to try again", score);
    else if (score < HIGH_RESULT) 
        swprintf_s(message, 120, L"Your score: %d \nAmazing result! \n\nPress Enter to try again", score);
    else 
        swprintf_s(message, 120, L"Your score: %d \nThis is crazy! \n\nPress Enter to try again", score);
    HWND messageBox = MessageBoxW(hWindowMain, message, L"Game Over", MB_OK);

    return 1;
}

int generateFood(RECT PlayGroundInBlocks, HWND hWindowMain)
{
    // need to try make it function async
    Point food = { 0 };
    do
    {
        food.x = rand() * PlayGroundInBlocks.right / RAND_MAX;
        food.y = rand() * PlayGroundInBlocks.bottom / RAND_MAX;
    } while (PlayGroundMap[food.x][food.y] != EMPTY);

    PlayGroundMap[food.x][food.y] = FOOD;
    
    foodBonus = MAX_BONUS;
    SetTimer(hWindowMain, FOOD_TIMER, snake.bonusSpeed, NULL);

    return 1;
}