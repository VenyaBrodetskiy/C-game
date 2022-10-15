#include "init.interface.h"

extern WCHAR szTitle[MAX_LOADSTRING], szWindowClass[MAX_LOADSTRING];
extern HINSTANCE    hInst;
extern HWND hButtonStart, hStaticText1, hDynamicText1;

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

    HWND hWindowMain = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        0, 0, PlayGroundInPixels.right + BUTTON1_SIZE_X + 17, PlayGroundInPixels.bottom + 39, NULL, NULL, hInstance, NULL);
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
    hButtonStart = CreateWindowW(L"button", L"Start game",
        WS_VISIBLE | WS_CHILD,
        PlayGroundInPixels.right + 1, 0, BUTTON1_SIZE_X, BUTTON1_SIZE_Y,
        hWindowMain, (HMENU)BUTTON_START, 0, NULL);

    CreateWindowW(L"Button", L"Choose mode",
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        PlayGroundInPixels.right + 1, BUTTON1_SIZE_Y + STAT_TEXT1_Y + 10, STAT_TEXT1_X + DYN_TEXT1_X, 80,
        hWindowMain, (HMENU)GROUP_BOX, 0, NULL);
    CreateWindowW(L"Button", L"No walls",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        PlayGroundInPixels.right + 4, BUTTON1_SIZE_Y + STAT_TEXT1_Y + 30, STAT_TEXT1_X + DYN_TEXT1_X, STAT_TEXT1_Y,
        hWindowMain, (HMENU)RADIO_NOWALLS, 0, NULL);
    HWND radioButtonWalls = CreateWindowW(L"Button", L"With walls",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        PlayGroundInPixels.right + 4, BUTTON1_SIZE_Y + STAT_TEXT1_Y + 30 + STAT_TEXT1_Y, STAT_TEXT1_X + DYN_TEXT1_X, STAT_TEXT1_Y,
        hWindowMain, (HMENU)RADIO_WALLS, 0, NULL);
    // set button to be checked by default
    SendMessageW(radioButtonWalls, BM_SETCHECK, BST_CHECKED, 0);

    return TRUE;
}

int createLabels(HWND hWindowMain, RECT PlayGroundInPixels)
{
    hStaticText1 = CreateWindowW(L"static", L"Points: ",
        WS_CHILD | WS_VISIBLE,
        PlayGroundInPixels.right + 1, BUTTON1_SIZE_Y, STAT_TEXT1_X, STAT_TEXT1_Y,
        hWindowMain, (HMENU)STATIC_TEXT1, NULL, NULL);

    hDynamicText1 = CreateWindowW(L"static", L"0",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        PlayGroundInPixels.right + STAT_TEXT1_X + 1, BUTTON1_SIZE_Y, DYN_TEXT1_X, DYN_TEXT1_Y,
        hWindowMain, (HMENU)DYNAMIC_TEXT1, NULL, NULL);

    return TRUE;
}