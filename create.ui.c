#include "params.game.h"
#include "params.ui.h"

#include "common_entities.h"

#include "create.ui.h"

#include <commctrl.h>

extern WCHAR szTitle[MAX_LOADSTRING], szWindowClass[MAX_LOADSTRING];
extern HINSTANCE    hInst;
extern HWND hWindowMain, hButtonStart, hButtonPause, hStaticText, hDynamicText, hTrackBar, hProgressBar;

int initGameButtons(HWND hWindowMain, RECT_ PlayGroundInPixels);
int initRadioButtons(HWND hWindowMain, RECT_ PlayGroundInPixels);
int initTrackBar(HWND hWindowMain, RECT_ PlayGroundInPixels);
int initTips(HWND hWindowMain, RECT_ PlayGroundInPixels);
int initBonusBarAndScore(HWND hWindowMain, RECT_ PlayGroundInPixels);


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//          venya: changed name to InitMainWindow
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitMainWindow(HINSTANCE hInstance, int nCmdShow, RECT_ PlayGroundInPixels)
{
    hInst = hInstance; // Store instance handle in our global variable

    // store main window in global variable also
    hWindowMain = CreateWindowW(szWindowClass, L"Snake Game", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        0, 0, PlayGroundInPixels.right + BUTTON_WIDTH + 20, PlayGroundInPixels.bottom + 39, NULL, NULL, hInstance, NULL);
    // 17 and 40 are just numbers to make it more beautiful. later change to expressions

    if (!hWindowMain)
    {
        return FALSE;
    }

    ShowWindow(hWindowMain, nCmdShow);
    UpdateWindow(hWindowMain);

    return TRUE;
}

int createButtons(HWND hWindowMain, RECT_ PlayGroundInPixels)
{
    initGameButtons(hWindowMain, PlayGroundInPixels);

    initRadioButtons(hWindowMain, PlayGroundInPixels);

    initTrackBar(hWindowMain, PlayGroundInPixels);

    initTips(hWindowMain, PlayGroundInPixels);

    initBonusBarAndScore(hWindowMain, PlayGroundInPixels);   

    return TRUE;
}

int initGameButtons(HWND hWindowMain, RECT_ PlayGroundInPixels)
{
    hButtonStart = CreateWindowW(L"Button", L"New game",
        WS_VISIBLE | WS_CHILD,
        PlayGroundInPixels.right + SPACE_PIXEL, 0, BUTTON_WIDTH, BUTTON_HEIGHT,
        hWindowMain, (HMENU)BUTTON_START, 0, NULL);
    hButtonPause = CreateWindowW(L"Button", L"Pause",
        WS_CHILD | WS_VISIBLE,
        PlayGroundInPixels.right + SPACE_PIXEL, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT,
        hWindowMain, (HMENU)BUTTON_PAUSE, NULL, NULL);

    return 1;
}

int initRadioButtons(HWND hWindowMain, RECT_ PlayGroundInPixels)
{
    CreateWindowW(L"Button", L"Game mode",
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        PlayGroundInPixels.right + SPACE_PIXEL, 2 * BUTTON_HEIGHT, BUTTON_WIDTH, GROUP_BOX_HEIGHT,
        hWindowMain, (HMENU)GROUP_BOX1, 0, NULL);
    CreateWindowW(L"Button", L"No walls",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        PlayGroundInPixels.right + 2 * SPACE_PIXEL, 2 * BUTTON_HEIGHT + 20, RADIO_BTN_WIDTH, RADIO_BTN_HEIGHT,
        hWindowMain, (HMENU)RADIO_NOWALLS, 0, NULL);
    HWND hRadioButtonWalls = CreateWindowW(L"Button", L"With walls",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        PlayGroundInPixels.right + 2 * SPACE_PIXEL, 2 * BUTTON_HEIGHT + 20 + RADIO_BTN_HEIGHT, RADIO_BTN_WIDTH, RADIO_BTN_HEIGHT,
        hWindowMain, (HMENU)RADIO_WALLS, 0, NULL);
    // set button to be checked by default
    SendMessageW(hRadioButtonWalls, BM_SETCHECK, BST_CHECKED, 0);

    return 1;
}

int initTrackBar(HWND hWindowMain, RECT_ PlayGroundInPixels)
{
    CreateWindowW(L"Button", L"Snake Speed",
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        PlayGroundInPixels.right + SPACE_PIXEL, TRACKBAR_Y, BUTTON_WIDTH, GROUP_BOX_HEIGHT,
        hWindowMain, (HMENU)SPEED_LABEL, 0, NULL);
    hTrackBar = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Control",
        WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
        PlayGroundInPixels.right + SPACE_PIXEL, TRACKBAR_Y + TB_LABEL_H, BUTTON_WIDTH, TRACKBAR_HEIGHT,
        hWindowMain, (HMENU)TRACK_BAR, 0, NULL);
    CreateWindowW(L"Static", L"Fast",
        WS_CHILD | WS_VISIBLE,
        PlayGroundInPixels.right + SPACE_PIXEL, TRACKBAR_Y + TB_LABEL_H + TRACKBAR_HEIGHT, TB_LABEL_W, TB_LABEL_H,
        hWindowMain, (HMENU)STATIC_TEXT2, NULL, NULL);
    CreateWindowW(L"Static", L"Slow",
        WS_CHILD | WS_VISIBLE,
        PlayGroundInPixels.right + TB_RIGHT_LABEL_POS, TRACKBAR_Y + TB_LABEL_H + TRACKBAR_HEIGHT, TB_LABEL_W, TB_LABEL_H,
        hWindowMain, (HMENU)STATIC_TEXT3, NULL, NULL);
    
    SendMessageW(hTrackBar, TBM_SETRANGE,
        (WPARAM)TRUE,
        (LPARAM)MAKELONG(SPEED_MAX, SPEED_MIN)); // min and max positions
    SendMessageW(hTrackBar, TBM_SETTICFREQ, TB_TIC_FREQ, 0); // set frequency of ticks. Here we need just 3 ticks
    SendMessageW(hTrackBar, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)TB_DEFAULT_VALUE); // set default value

    return 1;
}

int initTips(HWND hWindowMain, RECT_ PlayGroundInPixels)
{
    CreateWindowW(L"static",
        L"Tips:\nMove - Arrows\nPause - Space\nNew - Enter",
        WS_CHILD | WS_VISIBLE,
        PlayGroundInPixels.right + SPACE_PIXEL, TIPS_Y, TIPS_WIDTH, TIPS_HEIGHT,
        hWindowMain, (HMENU)STATIC_TEXT1, NULL, NULL);

    return 1;
}

int initBonusBarAndScore(HWND hWindowMain, RECT_ PlayGroundInPixels)
{
    hProgressBar = CreateWindowW(PROGRESS_CLASSW, L"Trackbar Control",
        WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
        PlayGroundInPixels.right + SPACE_PIXEL, PlayGroundInPixels.bottom - 2 * DYN_TEXT_Y, BUTTON_WIDTH, PB_LABEL_H,
        hWindowMain, (HMENU)PROGRESS_BAR, NULL, NULL);
    SendMessageW(hProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, MAX_BONUS));
    CreateWindowW(L"static", L"Bonus:",
        WS_CHILD | WS_VISIBLE,
        PlayGroundInPixels.right + SPACE_PIXEL, PlayGroundInPixels.bottom - 2 * DYN_TEXT_Y - PB_LABEL_H, STAT_TEXT_X, PB_LABEL_H,
        hWindowMain, (HMENU)STATIC_TEXT1, NULL, NULL);

    hDynamicText = CreateWindowW(L"static", L"Score: ",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        PlayGroundInPixels.right + SPACE_PIXEL, PlayGroundInPixels.bottom - DYN_TEXT_Y - SPACE_PIXEL, BUTTON_WIDTH, DYN_TEXT_Y,
        hWindowMain, (HMENU)DYNAMIC_TEXT1, NULL, NULL);

    return 1;
}