#include "params.game.h"
#include "params.interface.h"

#include "common_entities.h"

#include "init.interface.h"
#include "update.interface.h"

#include "init.game.h"
#include "snake.game.h"
#include "game.paint.h"

#include "main.h"
#include <commctrl.h>

// Global Variables:
HINSTANCE    hInst;                                // current instance
WCHAR        szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR        szWindowClass[MAX_LOADSTRING];            // the main window class name
BOOL         isGameStarted = FALSE;
BOOL         isKeyDown = FALSE;
BOOL         isEnabledWalls = TRUE;
BOOL         isGamePaused = FALSE;

// All Button handlers
HWND hWindowMain;
HWND hButtonStart, hButtonPause, hStaticText, hDynamicText, hTrackBar, hProgressBar;

// snake
HDC hdc;
RECT_ PlayGroundInPixels, PlayGroundInBlocks;
Snake snake;
char **PlayGroundMap;
int foodBonus;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // get szTitle
    LoadStringW(hInstance, IDC_MYGAME, szWindowClass, MAX_LOADSTRING); // get szWindowClass
    MyRegisterClass(hInstance);
    
    // init Playground for Snake 
    PlayGroundInBlocks = GetPlayGroundInBlocks(FIELD_WIDTH, FIELD_HEIGHT);
    PlayGroundInPixels = GetPlayGroundInPixels(PlayGroundInBlocks, PIXEL_BLOCK);

    // Perform application initialization:
    if (!InitMainWindow(hInstance, nCmdShow, PlayGroundInPixels))
    {
        return FALSE;
    }

    // enable use of common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

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

            hdc = GetDC(hWindowMain);
            break;
        }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case BUTTON_START:
            isGameStarted = startNewGame(&snake, isEnabledWalls);
            break;
        case BUTTON_PAUSE:
            if (isGameStarted && isGamePaused)
            {
                isGamePaused = resumeGame(&snake);
            }
            else if (isGameStarted && !isGamePaused)
            {
                isGamePaused = pauseGame();
            }
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
        SetFocus(hWindowMain);
        break;
    }
    case WM_TIMER:
    {
        switch (wParam)
        {
        case GAME_TIMER:
            if (isGameStarted)
            {
                isKeyDown = FALSE;
                moveSnake(&snake);
                drawPlayGround(hdc, PlayGroundInPixels);
            }
            break;
        case FOOD_TIMER:
            if (foodBonus > 0)
            {
                foodBonus--;
                SendMessageW(hProgressBar, PBM_SETPOS, (WPARAM)foodBonus, 0);
            }
            break;
        }
    }
    case WM_KEYDOWN:
        isKeyDown = changeSnakeDirection(wParam, &snake, isKeyDown);
        break;
    case WM_KEYUP:
        if (wParam == VK_RETURN && (!isGameStarted || isGamePaused))
            startNewGame(&snake, isEnabledWalls);
        
        if (wParam == VK_SPACE && isGameStarted && isGamePaused)
        {
            isGamePaused = resumeGame(&snake);
        }
        else if (wParam == VK_SPACE && isGameStarted && !isGamePaused)
        {
            isGamePaused = pauseGame();
        }

        break;
    case WM_HSCROLL:
        SetFocus(hWindowMain);

        // if would like to change speed while game is running (I thing this is like cheating)
        //snake.speed = (int)SendMessageW(hTrackBar, TBM_GETPOS, 0, 0);
        //SetTimer(hWindowMain, GAME_TIMER, snake.speed, NULL);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            // hdc is handle to device context
            HDC hdc = BeginPaint(hWindowMain, &ps);

            if (!isGameStarted)
            {
                drawGameField(hdc, PlayGroundInPixels);
                drawGameTips(hdc, PlayGroundInPixels);
            }
            else
            {
                drawPlayGround(hdc, PlayGroundInPixels);
            }

            EndPaint(hWindowMain, &ps);
        }
        break;
    case WM_SIZE:
        // currently no need to use, as window size is frozen
        //MoveAllButtons(hWindowMain, PlayGroundInPixels);
        switch (wParam)
        {
        case SIZE_MINIMIZED:
            isGamePaused = pauseGame();
            break;
        case SIZE_RESTORED:
            if (isGameStarted && !isGamePaused)
            {
                isGamePaused = resumeGame(&snake);
            }
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        free(PlayGroundMap);
        break;
    default:
        return DefWindowProcW(hWindowMain, message, wParam, lParam);
    }
    return 0;
}

