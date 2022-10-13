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

int createButtons(HWND hWindowMain)
{
    RECT ClientRect;

    GetClientRect(hWindowMain, &ClientRect);

    hButtonStart = CreateWindowW(L"button", L"Start game",
        WS_VISIBLE | WS_CHILD,
        ClientRect.right - BUTTON1_SIZE_X, 0, BUTTON1_SIZE_X, BUTTON1_SIZE_Y,
        hWindowMain, (HMENU)BUTTON_START, 0, NULL);

    return TRUE;
}

int createLabels(HWND hWindowMain)
{
    RECT ClientRect;

    GetClientRect(hWindowMain, &ClientRect);

    hStaticText1 = CreateWindowW(L"static", L"Counter: ",
        WS_CHILD | WS_VISIBLE,
        ClientRect.right - BUTTON1_SIZE_X, BUTTON1_SIZE_Y, 55, 25,
        hWindowMain, (HMENU)1, NULL, NULL);

    hDynamicText1 = CreateWindowW(L"static", L"0",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        ClientRect.right - BUTTON1_SIZE_X + 55, BUTTON1_SIZE_Y, 45, 25,
        hWindowMain, (HMENU)2, NULL, NULL);

    return TRUE;
}