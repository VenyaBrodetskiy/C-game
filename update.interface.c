#include "update.interface.h"
// currently this module is not used, because screen
extern HWND hButtonStart, hStaticText1, hDynamicText1;

int MoveAllButtons(HWND hWindowMain, RECT GameField)
{
    SetWindowPos(hButtonStart, NULL,
        GameField.right, 0,
        0, 0, SWP_NOSIZE);

    SetWindowPos(hStaticText1, NULL,
        GameField.right, BUTTON_SIZE_Y,
        0, 0, SWP_NOSIZE);

    SetWindowPos(hDynamicText1, NULL,
        GameField.right + STAT_TEXT1_X, BUTTON_SIZE_Y,
        0, 0, SWP_NOSIZE);

    return 1;
}