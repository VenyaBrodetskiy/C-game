#include "update.interface.h"
extern HWND hButtonStart, hStaticText, hDynamicText;

int updateScore(HWND hDynamicText, int score)
{
    wchar_t scoreString[15];
    swprintf_s(scoreString, 15, L"Score: %d", score);

    SetWindowTextW(hDynamicText, scoreString);

    return 1;
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