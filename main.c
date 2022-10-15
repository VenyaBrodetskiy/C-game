// MyGame.cpp : Defines the entry point for the application.
#include "main.h"

// Global Variables:
HINSTANCE    hInst;                                // current instance
WCHAR        szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR        szWindowClass[MAX_LOADSTRING];            // the main window class name
BOOL         isGameStarted = FALSE;
BOOL         isKeyDown = FALSE;
BOOL         isEnabledWalls = TRUE;

// All Button handlers
HWND hButtonStart; // init button
HWND hStaticText1;
HWND hDynamicText1; // init global text-window

// snake
HDC hdc;
RECT PlayGroundInPixels;
RECT PlayGroundInBlocks;
Snake snake;
char PlayGroundMap[200][100];

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // get szTitle
    LoadStringW(hInstance, IDC_MYGAME, szWindowClass, MAX_LOADSTRING); // get szWindowClass
    MyRegisterClass(hInstance);
    
    // init Playground for Snake 
    PlayGroundInBlocks = CreatePlayGround(FIELD_WIDTH, FIELD_HEIGHT);
    PlayGroundInPixels = GetPlayGroundInPixels(PlayGroundInBlocks, PIXEL_BLOCK);

    // Perform application initialization:
    if (!InitMainWindow(hInstance, nCmdShow, PlayGroundInPixels))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCE(IDC_MYGAME));

    MSG msg = { 0 };
    // Main message loop:
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        if (!TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
            
        }
    }
    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW WindowClass = { 0 };

    WindowClass.cbSize = sizeof(WNDCLASSEX);

    WindowClass.style          = CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc    = MainWindowProcedure; // pointer to the function 
    WindowClass.cbClsExtra     = 0;
    WindowClass.cbWndExtra     = 0;
    WindowClass.hInstance      = hInstance;
    WindowClass.hIcon          = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_MYGAME));
    WindowClass.hCursor        = LoadCursorW(NULL, IDC_ARROW);
    WindowClass.hbrBackground  = (HBRUSH)(COLOR_WINDOW); 
    WindowClass.lpszMenuName   = MAKEINTRESOURCEW(NULL); 
    WindowClass.lpszClassName  = szWindowClass;
    WindowClass.hIconSm        = LoadIconW(WindowClass.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&WindowClass);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//          (venya: I changed name to MainWindowProcedure)
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK MainWindowProcedure(HWND hWindowMain, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            createButtons(hWindowMain, PlayGroundInPixels);
            createLabels(hWindowMain, PlayGroundInPixels);

            hdc = GetDC(hWindowMain);
            break;
        }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case BUTTON_START:
            isGameStarted = startNewGame(hWindowMain);
            break;
        case RADIO_NOWALLS:
            isEnabledWalls = FALSE;
            break;
        case RADIO_WALLS:
            isEnabledWalls = TRUE;
            break;
        default:
            return DefWindowProcW(hWindowMain, message, wParam, lParam);
        }
    }
    break;
    case WM_TIMER:
    {
        if (isGameStarted)
        {
            isKeyDown = FALSE;
            moveSnake(hWindowMain);
            drawPlayGround(hWindowMain, hdc, PlayGroundInPixels);
        }
        
    }
    case WM_KEYDOWN:
        isKeyDown = changeSnakeDirection(wParam, isKeyDown);
        break;

    case WM_KEYUP:
        if (wParam == VK_RETURN && !isGameStarted) isGameStarted = startNewGame(hWindowMain);
        break;
    
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            // hdc is handle to device context
            HDC hdc = BeginPaint(hWindowMain, &ps);

            paintGameField(hdc, PlayGroundInPixels);

            EndPaint(hWindowMain, &ps);
        }
        break;
    case WM_SIZE:
        // currently no need to use, as window size is frozen
        //MoveAllButtons(hWindowMain, PlayGroundInPixels);
        switch (wParam)
        {
        case SIZE_MINIMIZED:
            KillTimer(hWindowMain, GAME_TIMER);
            break;
        case SIZE_RESTORED:
            if (isGameStarted) SetTimer(hWindowMain, GAME_TIMER, DEFAULT_SPEED, NULL);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWindowMain, message, wParam, lParam);
    }
    return 0;
}

BOOL startNewGame(HWND hWindowMain)
{
    initPlayGround(PlayGroundInBlocks, isEnabledWalls);
    initSnake(PlayGroundInBlocks);
    SetTimer(hWindowMain, GAME_TIMER, DEFAULT_SPEED, NULL);
    SetFocus(hWindowMain);

    return TRUE;
}
