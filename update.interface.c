#include "update.interface.h"
extern HWND hButtonStart, hStaticText1, hDynamicText1;

int MoveAllButtons(HWND hWindowMain, RECT GameField)
{
    SetWindowPos(hButtonStart, NULL,
        GameField.right, 0,
        0, 0, SWP_NOSIZE);

    SetWindowPos(hStaticText1, NULL,
        GameField.right, BUTTON1_SIZE_Y,
        0, 0, SWP_NOSIZE);

    SetWindowPos(hDynamicText1, NULL,
        GameField.right + STAT_TEXT1_X, BUTTON1_SIZE_Y,
        0, 0, SWP_NOSIZE);

    return 1;
}

RECT GetGameFieldSize(HWND hWindowMain)
{
    RECT GameFieldRect;
    GetClientRect(hWindowMain, &GameFieldRect);
    GameFieldRect.right -= BUTTON1_SIZE_X;

    return GameFieldRect;
}