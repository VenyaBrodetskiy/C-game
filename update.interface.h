#pragma once

#ifdef GAME_FOR_WIN_API
	// if not WINDOWS, KEYDOWN is not wParam, please make typedef for localKEYDOWN
	#define VK_LEFT		0x25
	#define VK_UP		0x26
	#define VK_RIGHT	0x27
	#define VK_DOWN		0x28
#endif

ControlUI* initializeControlUI();

BOOL destructControlUI(ControlUI* controlUI);

int  updateScore(int score);
int  getSnakeSpeed();
void setButtonContinue();
void setButtonPause();
void createTimer(int timer, int speed);
void stopTimer(int timer);
void popUpGameOver(wchar_t message[]);
//int  MoveAllButtons(HWND hWindowMain, RECT_ GameField);