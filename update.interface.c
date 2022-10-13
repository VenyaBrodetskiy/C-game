#include "update.interface.h"
extern HWND hButtonStart, hStaticText1, hDynamicText1;

int MoveAllButtons(HWND hWindowMain)
{
    RECT ClientRect;
    GetClientRect(hWindowMain, &ClientRect);
    SetWindowPos(hButtonStart, NULL,
        ClientRect.right - BUTTON1_SIZE_X, 0,
        0, 0, SWP_NOSIZE);

    SetWindowPos(hStaticText1, NULL,
        ClientRect.right - BUTTON1_SIZE_X, BUTTON1_SIZE_Y,
        0, 0, SWP_NOSIZE);

    SetWindowPos(hDynamicText1, NULL,
        ClientRect.right - BUTTON1_SIZE_X + 55, BUTTON1_SIZE_Y,
        0, 0, SWP_NOSIZE);

    return 1;
}