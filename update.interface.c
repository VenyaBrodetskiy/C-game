#include "update.interface.h"
extern HWND hWindowMain, hButtonStart, hStaticText, hDynamicText, hTrackBar;

int updateScore(int score)
{
    wchar_t scoreString[15];
    swprintf_s(scoreString, 15, L"Score: %d", score);

    SetWindowTextW(hDynamicText, scoreString);

    return 1;
}

int getSnakeSpeed()
{
    return (int)SendMessageW(hTrackBar, TBM_GETPOS, 0, 0);
}

void stopTimer(int timer)
{
    KillTimer(hWindowMain, timer);
}

void popUpGameOver(wchar_t message)
{
    MessageBoxW(hWindowMain, message, L"Game Over", MB_OK);
}

// currently this function is not used, because screen size is fixed
int MoveAllButtons(HWND hWindowMain, RECT GameField)
{
    SetWindowPos(hButtonStart, NULL,
        GameField.right, 0,
        0, 0, SWP_NOSIZE);

    SetWindowPos(hStaticText, NULL,
        GameField.right, BUTTON_HEIGHT,
        0, 0, SWP_NOSIZE);

    SetWindowPos(hDynamicText, NULL,
        GameField.right + STAT_TEXT_X, BUTTON_HEIGHT,
        0, 0, SWP_NOSIZE);

    return 1;
}