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
BOOL InitMainWindow(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWindowMain = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWindowMain)
    {
        return FALSE;
    }

    ShowWindow(hWindowMain, nCmdShow);
    UpdateWindow(hWindowMain);

    return TRUE;
}

int createButtons(HWND hWindowMain, RECT GameFieldRect)
{
    hButtonStart = CreateWindowW(L"button", L"Start game",
        WS_VISIBLE | WS_CHILD,
        GameFieldRect.right, 0, BUTTON1_SIZE_X, BUTTON1_SIZE_Y,
        hWindowMain, (HMENU)BUTTON_START, 0, NULL);

    return TRUE;
}

int createLabels(HWND hWindowMain, RECT GameFieldRect)
{
    hStaticText1 = CreateWindowW(L"static", L"Counter: ",
        WS_CHILD | WS_VISIBLE,
        GameFieldRect.right, BUTTON1_SIZE_Y, STAT_TEXT1_X, STAT_TEXT1_Y,
        hWindowMain, (HMENU)1, NULL, NULL);

    hDynamicText1 = CreateWindowW(L"static", L"0",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        GameFieldRect.right + 55, BUTTON1_SIZE_Y, DYN_TEXT1_X, DYN_TEXT1_Y,
        hWindowMain, (HMENU)2, NULL, NULL);

    return TRUE;
}