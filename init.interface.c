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
        CW_USEDEFAULT, 0, PlayGroundInPixels.right + BUTTON1_SIZE_X + 17, PlayGroundInPixels.bottom + 39, NULL, NULL, hInstance, NULL);
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
        PlayGroundInPixels.right, 0, BUTTON1_SIZE_X, BUTTON1_SIZE_Y,
        hWindowMain, (HMENU)BUTTON_START, 0, NULL);

    return TRUE;
}

int createLabels(HWND hWindowMain, RECT PlayGroundInPixels)
{
    hStaticText1 = CreateWindowW(L"static", L"Points: ",
        WS_CHILD | WS_VISIBLE,
        PlayGroundInPixels.right, BUTTON1_SIZE_Y, STAT_TEXT1_X, STAT_TEXT1_Y,
        hWindowMain, (HMENU)1, NULL, NULL);

    hDynamicText1 = CreateWindowW(L"static", L"0",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        PlayGroundInPixels.right + STAT_TEXT1_X, BUTTON1_SIZE_Y, DYN_TEXT1_X, DYN_TEXT1_Y,
        hWindowMain, (HMENU)2, NULL, NULL);

    return TRUE;
}

RECT CreatePlayGround(int widthBlock, int heightBlock)
{
    RECT PlayGroundInBlocks;
    PlayGroundInBlocks.left = 1;
    PlayGroundInBlocks.top = 1;
    PlayGroundInBlocks.bottom = heightBlock;
    PlayGroundInBlocks.right = widthBlock;

    return PlayGroundInBlocks;
}

RECT GetPlayGroundInPixels(RECT PlayGroundInBlocks, int pixelBlock)
{
    RECT PlayGroundInPixels;
    PlayGroundInPixels.left = 0;
    PlayGroundInPixels.top = 0;
    PlayGroundInPixels.right = PlayGroundInBlocks.right * pixelBlock;
    PlayGroundInPixels.bottom = PlayGroundInBlocks.bottom * pixelBlock;

    return PlayGroundInPixels;
}