// MyGame.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include <strsafe.h>
#include "MyGame.h"

#define MAX_LOADSTRING 100
#define ID_HOTKEY_1 1 // for hot key Ctrl + C
#define C_BUTTON 0x43 // code of "C" from keyboard

#define BUTTON_START 3 // N of button
#define BUTTON1_SIZE_X 100
#define BUTTON1_SIZE_Y 30

// Global Variables:
HINSTANCE    hInst;                                // current instance
WCHAR        szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR        szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND         hWindowMain = { 0 };

// All Button handlers
HWND hButtonStart; // init button
HWND hStaticText1;
HWND hDynamicText1; // init global text-window
int counter = 0;

// snake
RECT snake = { 0 };


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
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    /////////////// playground ///////////////////////
    //usefull_staff(hWindowMain);
    
   
    /////////////// playground ///////////////////////

    HACCEL hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCE(IDC_MYGAME));

    MSG msg = { 0 };
    HDC hdc = GetDC(hWindowMain);

    // Main message loop:
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        if (!TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
            
        }
        moveSnake();
        paintSnake(hWindowMain, hdc);
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
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
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
            createButtons(hWindowMain);
            createLabels(hWindowMain);
            initSnake(hWindowMain);
            //hLabel1 = CreateLabel(hWindowMain);
            break;
        }
    case WM_HOTKEY:
        // change text on screen by hotkey
        { 
            if (wParam == ID_HOTKEY_1) {
                counterIncrease();
            }
            break;
        }   

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case BUTTON_START:
                {
                    counterIncrease();
                    break;
                }

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

            paintGameField(hWindowMain, hdc);

            //paintSnake(hWindowMain, hdc);

            EndPaint(hWindowMain, &ps);

        }
        break;
    case WM_SIZE:
        MoveAllButtons(hWindowMain);
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

int createButtons(HWND hWindowMain)
{ 
    RECT ClientRect;

    GetClientRect(hWindowMain, &ClientRect);

    hButtonStart = CreateWindowW(L"button", L"Counter + 1", 
        WS_VISIBLE | WS_CHILD,
        ClientRect.right - BUTTON1_SIZE_X, 0, BUTTON1_SIZE_X, BUTTON1_SIZE_Y,
        hWindowMain, BUTTON_START, NULL, NULL);
    
    return TRUE;
}

int createLabels(HWND hWindowMain)
{
    RECT ClientRect;

    GetClientRect(hWindowMain, &ClientRect);

    hStaticText1 = CreateWindowW(L"static", L"Counter: ",
        WS_CHILD | WS_VISIBLE,
        ClientRect.right - BUTTON1_SIZE_X, BUTTON1_SIZE_Y, 55, 25,
        hWindowMain, (HMENU) 1, NULL, NULL);

    hDynamicText1 = CreateWindowW(L"static", L"0",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        ClientRect.right - BUTTON1_SIZE_X + 55, BUTTON1_SIZE_Y, 45, 25,
        hWindowMain, (HMENU) 2, NULL, NULL);

    return TRUE;
}

int MoveAllButtons(HWND hWindowMain)
{
    RECT ClientRect;
    GetClientRect(hWindowMain, &ClientRect);
    SetWindowPos(hButtonStart, NULL,
        ClientRect.right - BUTTON1_SIZE_X, 0,
        NULL, NULL, SWP_NOSIZE);

    SetWindowPos(hStaticText1, NULL,
        ClientRect.right - BUTTON1_SIZE_X, BUTTON1_SIZE_Y,
        NULL, NULL, SWP_NOSIZE);

    SetWindowPos(hDynamicText1, NULL,
        ClientRect.right - BUTTON1_SIZE_X + 55, BUTTON1_SIZE_Y,
        NULL, NULL, SWP_NOSIZE);

    return 1;
}

int counterIncrease()
{
    counter++;
    
    wchar_t buf[10];
    UINT buf_len = 10;

    StringCbPrintfW(buf, buf_len, L"%d", counter);
    SetWindowTextW(hDynamicText1, buf);

    return 1;
}

int paintGameField(HWND hWindowMain, HDC hdc)
{
    RECT ClientRect;

    GetClientRect(hWindowMain, &ClientRect);

    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Rectangle(hdc, ClientRect.left, ClientRect.top, ClientRect.right - BUTTON1_SIZE_X, ClientRect.bottom);
   
    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);

    DeleteObject(hPen);
    DeleteObject(hOldBrush);
}

int initSnake(HWND hWindowMain)
{
    RECT GameFieldRect;
    GetClientRect(hWindowMain, &GameFieldRect);
    GameFieldRect.right -= BUTTON1_SIZE_X;

    snake.left = (GameFieldRect.right - GameFieldRect.left) / 2;
    snake.right = snake.left + 50;
    snake.top = (GameFieldRect.bottom - GameFieldRect.top) / 2;
    snake.bottom = snake.top + 10;
}

int paintSnake(HWND hWindowMain, HDC hdc)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 200));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Rectangle(hdc, snake.left, snake.top, snake.right, snake.bottom);
    
    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hOldBrush);

    return 1;
}

int moveSnake()
{
    snake.left += 1;
    snake.right += 1;
    Sleep(10);
}