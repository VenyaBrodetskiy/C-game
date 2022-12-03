#pragma once

int  updateScore(int score);
int  getSnakeSpeed();
void setButtonContinue();
void setButtonPause();
void createTimer(int timer, int speed);
void stopTimer(int timer);
void popUpGameOver(wchar_t message[]);
void beep();
//int  MoveAllButtons(HWND hWindowMain, RECT_ GameField);