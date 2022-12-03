#include "params.ui.h"
#include "common_entities.h"

#include <tchar.h>
#include "windows.h" 

#include "control.ui.h"
#include "private.control.ui.h"

#include <commctrl.h>

extern HWND hWindowMain, hButtonStart, hStaticText, hDynamicText, hTrackBar, hButtonPause;

ControlUI* initializeControlUI()
{
    ControlUI* controlUI = malloc(sizeof(ControlUI));

    if (controlUI == NULL) {
        return NULL;
    }

    controlUI->updateScore_f = updateScore;
    controlUI->getSnakeSpeed_f = getSnakeSpeed;
    controlUI->setButtonContinue_f = setButtonContinue;
    controlUI->setButtonPause_f = setButtonPause;
    controlUI->createTimer_f = createTimer;
    controlUI->stopTimer_f = stopTimer;
    controlUI->popUpGameOver_f = popUpGameOver;
    controlUI->beep_f = beep;
    return controlUI;
}

void destructControlUI(ControlUI* controlUI)
{
    free(controlUI);
}

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

void setButtonContinue()
{
    SetWindowTextW(hButtonPause, L"Continue..");
}

void setButtonPause()
{
    SetWindowTextW(hButtonPause, L"Pause");
}


// maybe better to move these functions to other (game helpers)
void createTimer(int timer, int speed)
{
    SetTimer(hWindowMain, timer, speed, NULL);
}

// maybe better to move these functions to other (game helpers)
void stopTimer(int timer)
{
    KillTimer(hWindowMain, timer);
}

void popUpGameOver(wchar_t message[])
{
    MessageBoxW(hWindowMain, message, L"Game Over", MB_OK);
}

void beep()
{
    Beep(2000, 10);
}
// currently this function is not used, because screen size is fixed
int MoveAllButtons(HWND hWindowMain, RECT_ GameField)
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
