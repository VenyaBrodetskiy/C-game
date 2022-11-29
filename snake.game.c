#include "common_entities.h"

#include "init.game.h"
#include "snake.game.h"
#include "update.interface.h"

#include <stdlib.h>
#include <stdio.h>

#include "linked.list.h"
// instead of including make dependency injection
// function updateScore, stopTimer, popUpWindow send as pointers to functions

BOOL changeSnakeDirection(KEYDOWN keyDown, Snake* snake, BOOL isKeyDown)
{   
    switch (*keyDown)
    {
    case VK_UP:
        if (snake->direct != DOWN && !isKeyDown) 
        {
            snake->direct = UP;
            isKeyDown = TRUE;
        }
        break;
    case VK_DOWN:
        if (snake->direct != UP && !isKeyDown)
        {
            snake->direct = DOWN;
            isKeyDown = TRUE;
        }
        break;
    case VK_LEFT:
        if (snake->direct != RIGHT && !isKeyDown)
        {
            snake->direct = LEFT;
            isKeyDown = TRUE;
        }
        break;
    case VK_RIGHT:
        if (snake->direct != LEFT && !isKeyDown)
        {
            snake->direct = RIGHT;
            isKeyDown = TRUE;
        }
        break;
    }

    return isKeyDown;
}

void moveSnake(Snake* snake, char** PlayGroundMap, RECT_ PlayGroundInBlocks)
{
    Point* head = (Point*)list_get_head_data(snake->body);
    Point* tail = (Point*)list_get_tail_data(snake->body);

    Point* new_head = malloc(sizeof(Point));
    new_head->x = head->x;
    new_head->y = head->y;

    // count next step
    switch (snake->direct)
    {
    case RIGHT:
        new_head->x++;
        break;
    case LEFT:
        new_head->x--;
        break;
    case UP:
        new_head->y--;
        break;
    case DOWN:
        new_head->y++;
        break;
    }

    // check if head is within PlayGround
    if (new_head->x < 0) new_head->x = PlayGroundInBlocks.right - 1;
    if (new_head->x > PlayGroundInBlocks.right - 1) new_head->x = 0;
    if (new_head->y < 0) new_head->y = PlayGroundInBlocks.bottom - 1;
    if (new_head->y > PlayGroundInBlocks.bottom - 1) new_head->y = 0;

    // check if head hit the wall / body / food / nothing
    switch (PlayGroundMap[new_head->x][new_head->y])
    {
    case WALL:
    case SNAKE:
    {
        gameOver(snake);
    }
        break;
    case FOOD:
    {
        Beep(2000, 10);

        // update score
        snake->score = snake->score + SCORE_INCREMENT + snake->foodBonus;
        updateScore(snake->score);

        // update food
        stopTimer(FOOD_TIMER);
        generateFood(snake, PlayGroundMap, PlayGroundInBlocks);

        // update map
        PlayGroundMap[tail->x][tail->y] = EMPTY; // snake growth on next move after eating food 
        PlayGroundMap[new_head->x][new_head->y] = SNAKE;

        // update snake
        list_add_head(snake->body, new_head);
    }
    break;
    case EMPTY:
    {
        // update map
        PlayGroundMap[tail->x][tail->y] = EMPTY; // snake growth on next move after eating food 
        PlayGroundMap[new_head->x][new_head->y] = SNAKE;

        // update snake
        list_add_head(snake->body, new_head);
        list_remove_tail(snake->body);
    }
    break;
    }
}

void gameOver(Snake* snake)
{
    stopTimer(GAME_TIMER);
    stopTimer(FOOD_TIMER);
    snake->isGameStarted = FALSE;

    wchar_t message[120];
    if (snake->score < LOW_RESULT)
        swprintf_s(message, 120, L"Your score: %d \nTry to adjust settings \n\nPress Enter to try again", snake->score);
    else if (snake->score < AVERAGE_RESULT)
        swprintf_s(message, 120, L"Your score: %d \nכל הכבוד \n\nPress Enter to try again", snake->score);
    else if (snake->score < HIGH_RESULT)
        swprintf_s(message, 120, L"Your score: %d \nAmazing result! \n\nPress Enter to try again", snake->score);
    else 
        swprintf_s(message, 120, L"Your score: %d \nThis is crazy! \n\nPress Enter to try again", snake->score);
    
    popUpGameOver(message);

}

int generateFood(Snake* snake, char** PlayGroundMap, RECT_ PlayGroundInBlocks)
{
    // need to try make it function async
    Point food = { 0 };
    do
    {
        food.x = rand() * PlayGroundInBlocks.right / RAND_MAX;
        food.y = rand() * PlayGroundInBlocks.bottom / RAND_MAX;
    } while (PlayGroundMap[food.x][food.y] != EMPTY);

    PlayGroundMap[food.x][food.y] = FOOD;
    
    snake->foodBonus = MAX_BONUS;
    createTimer(FOOD_TIMER, snake->bonusSpeed);

    return 1;
}

char** startNewGame(Snake* snake, char** PlayGroundMap, RECT_ PlayGroundInBlocks, BOOL isEnabledWalls)
{
    PlayGroundMap = clearPlayGround(PlayGroundMap, PlayGroundInBlocks, isEnabledWalls);
    initSnake(snake, PlayGroundMap, PlayGroundInBlocks);

    generateFood(snake, PlayGroundMap, PlayGroundInBlocks); // inside this func food_timer is set

    createTimer(GAME_TIMER, snake->speed);

    setButtonPause();

    return PlayGroundMap;
}

void pauseGame(Snake* snake)
{
    stopTimer(GAME_TIMER);
    stopTimer(FOOD_TIMER);

    setButtonContinue();

    snake->isGamePaused = TRUE;
}

void resumeGame(Snake* snake)
{
    createTimer(GAME_TIMER, snake->speed);
    createTimer(FOOD_TIMER, snake->bonusSpeed);

    setButtonPause();

    snake->isGamePaused = FALSE;
}