#include "init.interface.h"

extern WCHAR szTitle[MAX_LOADSTRING], szWindowClass[MAX_LOADSTRING];
extern HINSTANCE    hInst;
extern HWND hButtonStart, hButtonPause, hStaticText1, hDynamicText1, hTrackBar, hProgressBar;

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
BOOL InitMainWindow(HINSTANCE hInstance, int nCmdShow, RECT PlayGroundInPixels)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWindowMain = CreateWindowW(szWindowClass, L"Snake Game", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        0, 0, PlayGroundInPixels.right + BUTTON_SIZE_X + 20, PlayGroundInPixels.bottom + 39, NULL, NULL, hInstance, NULL);
    // 17 and 40 are just numbers to make it more beautiful. later change to expressions

    if (!hWindowMain)
    {
        return FALSE;
    }

    ShowWindow(hWindowMain, nCmdShow);
    UpdateWindow(hWindowMain);

    return TRUE;
}

int createButtons(HWND hWindowMain, RECT PlayGroundInPixels)
{
    // New game button
    hButtonStart = CreateWindowW(L"Button", L"New game",
        WS_VISIBLE | WS_CHILD,
        PlayGroundInPixels.right + 1, 0, BUTTON_SIZE_X, BUTTON_SIZE_Y,
        hWindowMain, (HMENU)BUTTON_START, 0, NULL);
    hButtonPause = CreateWindowW(L"Button", L"Pause",
        WS_CHILD | WS_VISIBLE,
        PlayGroundInPixels.right + 1, BUTTON_SIZE_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y,
        hWindowMain, (HMENU)BUTTON_PAUSE, NULL, NULL);

    // Radiobuttons controlling Wall/NoWall game modes
    CreateWindowW(L"Button", L"Game mode",
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        PlayGroundInPixels.right + 1, BUTTON_SIZE_Y + STAT_TEXT1_Y + 10, STAT_TEXT1_X + DYN_TEXT1_X, 80,
        hWindowMain, (HMENU)GROUP_BOX1, 0, NULL);
    CreateWindowW(L"Button", L"No walls",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        PlayGroundInPixels.right + 4, BUTTON_SIZE_Y + STAT_TEXT1_Y + 30, STAT_TEXT1_X + DYN_TEXT1_X - 5, STAT_TEXT1_Y,
        hWindowMain, (HMENU)RADIO_NOWALLS, 0, NULL);
    HWND hRadioButtonWalls = CreateWindowW(L"Button", L"With walls",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        PlayGroundInPixels.right + 4, BUTTON_SIZE_Y + STAT_TEXT1_Y + 30 + STAT_TEXT1_Y, STAT_TEXT1_X + DYN_TEXT1_X - 5, STAT_TEXT1_Y,
        hWindowMain, (HMENU)RADIO_WALLS, 0, NULL);
    // set button to be checked by default
    SendMessageW(hRadioButtonWalls, BM_SETCHECK, BST_CHECKED, 0);

    // Trackbar controlling speed
    CreateWindowW(L"Button", L"Snake Speed",
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        PlayGroundInPixels.right + 1, BUTTON_SIZE_Y + STAT_TEXT1_Y + 30 + STAT_TEXT1_Y + STAT_TEXT1_Y + 10, STAT_TEXT1_X + DYN_TEXT1_X, 80,
        hWindowMain, (HMENU)SPEED_LABEL, 0, NULL);
    hTrackBar = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Control",
        WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
        PlayGroundInPixels.right + 1, BUTTON_SIZE_Y + STAT_TEXT1_Y + 30 + STAT_TEXT1_Y + STAT_TEXT1_Y + 30, STAT_TEXT1_X + DYN_TEXT1_X, 30, 
        hWindowMain, (HMENU)TRACK_BAR, 0, NULL);
    CreateWindowW(L"Static", L"Fast",
        WS_CHILD | WS_VISIBLE, 
        PlayGroundInPixels.right + 1, BUTTON_SIZE_Y + STAT_TEXT1_Y + 30 + STAT_TEXT1_Y + STAT_TEXT1_Y + 30 + 30, 35, 20,
        hWindowMain, (HMENU)STATIC_TEXT2, NULL, NULL);
    CreateWindowW(L"Static", L"Slow",
        WS_CHILD | WS_VISIBLE, 
        PlayGroundInPixels.right + 70, BUTTON_SIZE_Y + STAT_TEXT1_Y + 30 + STAT_TEXT1_Y + STAT_TEXT1_Y + 30 + 30, 35, 20,
        hWindowMain, (HMENU)STATIC_TEXT3, NULL, NULL);
    SendMessageW(hTrackBar, TBM_SETRANGE,
        (WPARAM)TRUE,
        (LPARAM)MAKELONG(20, 180)); // min and max positions
    SendMessageW(hTrackBar, TBM_SETTICFREQ, 80, 0); // set frequency of ticks. Here we need just 3 ticks
    SendMessageW(hTrackBar, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)100); // set default value

    // ProgressBar with bonus for food
    hProgressBar = CreateWindowW(PROGRESS_CLASSW, L"Trackbar Control",
        WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
        PlayGroundInPixels.right + 1, PlayGroundInPixels.bottom - 50, STAT_TEXT1_X + DYN_TEXT1_X, 20,
        hWindowMain, (HMENU)PROGRESS_BAR, NULL, NULL);
    SendMessageW(hProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
    CreateWindowW(L"static", L"Bonus:",
        WS_CHILD | WS_VISIBLE ,
        PlayGroundInPixels.right + 1, PlayGroundInPixels.bottom - 45 - DYN_TEXT1_Y, 80, 20,
        hWindowMain, (HMENU)STATIC_TEXT1, NULL, NULL);

    // Tips
    hStaticText1 = CreateWindowW(L"static",
        L"Tips:\nMove - Arrows\nPause - Space\nNew - Enter",
        WS_CHILD | WS_VISIBLE,
        PlayGroundInPixels.right + 1, BUTTON_SIZE_Y + 250, STAT_TEXT1_X + DYN_TEXT1_X, 100,
        hWindowMain, (HMENU)STATIC_TEXT1, NULL, NULL);

    // Total score
    hDynamicText1 = CreateWindowW(L"static", L"Score: ",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        PlayGroundInPixels.right + 1, PlayGroundInPixels.bottom - 27, STAT_TEXT1_X + DYN_TEXT1_X, DYN_TEXT1_Y,
        hWindowMain, (HMENU)DYNAMIC_TEXT1, NULL, NULL);

    return TRUE;
}

int createLabels(HWND hWindowMain, RECT PlayGroundInPixels)
{

    


    return TRUE;
}