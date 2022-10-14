// MyGame.cpp : Defines the entry point for the application.
#include "main.h"

// Global Variables:
HINSTANCE    hInst;                                // current instance
WCHAR        szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR        szWindowClass[MAX_LOADSTRING];            // the main window class name
BOOL         isGameStarted = FALSE;

// All Button handlers
HWND hButtonStart; // init button
HWND hStaticText1;
HWND hDynamicText1; // init global text-window
int counter = 0;

// snake
HDC hdc;
RECT GameFieldRect;
Snake snake;
char FieldMap[1920][1080];

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

    // Perform application initialization:
    if (!InitMainWindow(hInstance, nCmdShow))
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
    WindowClass.hbrBackground  = (HBRUSH)(COLOR_WINDOW); // GetSysColorBrush(COLOR_3DFACE);
    WindowClass.lpszMenuName   = MAKEINTRESOURCEW(NULL); //MAKEINTRESOURCEW(IDC_MYGAME);
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
            RegisterHotKey(hWindowMain, ID_HOTKEY_1, MOD_CONTROL, C_BUTTON);
            createButtons(hWindowMain, GameFieldRect);
            createLabels(hWindowMain, GameFieldRect);

            hdc = GetDC(hWindowMain);
            break;
        }
    case WM_TIMER:
    {
        if (isGameStarted)
        { 
            moveSnake(hWindowMain, GameFieldRect);
            paintSnake(hWindowMain, hdc, GameFieldRect);
        }
        
    }
    case WM_HOTKEY:
        // change text on screen by hotkey
        { 
            if (wParam == ID_HOTKEY_1) {
                counterIncrease();
            }
            break;
        }   

    case WM_KEYDOWN:
        changeSnakeDirection(wParam);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case BUTTON_START:
                isGameStarted = TRUE;
                // TODO: When Game is started need to restrict window size changes
                initYard(GameFieldRect);
                initSnake(hWindowMain, GameFieldRect);
                SetTimer(hWindowMain, 2, 16, NULL); // approx 60 fps
                SetFocus(hWindowMain);
                break;
            // below part is not needed, as I removed MENU from main window
            /*case IDM_ABOUT:
                DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_ABOUTBOX), hWindowMain, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWindowMain);
                break;*/
            default:
                return DefWindowProcW(hWindowMain, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            // hdc is handle to device context
            HDC hdc = BeginPaint(hWindowMain, &ps);

            paintGameField(hdc, GameFieldRect);

            EndPaint(hWindowMain, &ps);
        }
        break;
    case WM_SIZE:
        GameFieldRect = GetGameFieldSize(hWindowMain);
        MoveAllButtons(hWindowMain, GameFieldRect);
        break;
    case WM_DESTROY:
        UnregisterHotKey(hWindowMain, ID_HOTKEY_1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWindowMain, message, wParam, lParam);
    }
    return 0;
}

// below part is not needed, as I removed MENU from main window

// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}

int counterIncrease()
{
    counter++;
    
    wchar_t buf[10];
    UINT buf_len = 10;

    StringCbPrintfW(buf, buf_len, L"%d", counter);
    SetWindowTextW(hDynamicText1, buf);

    return 1;
}
