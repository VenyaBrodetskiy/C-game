// MyGame.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include <strsafe.h>
#include "MyGame.h"

#define MAX_LOADSTRING 100
#define ID_HOTKEY_1 1 // for hot key Ctrl + C
#define C_BUTTON 0x43 // code of "C" from keyboard
#define BUTTON_COUNTER 3 // N of button

// Global Variables:
HINSTANCE    hInst;                                // current instance
WCHAR        szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR        szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND button_counter; // init button
HWND hDynamicText1; // init global text-window
int counter = 0;


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
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYGAME));

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
    WindowClass.hbrBackground  = GetSysColorBrush(COLOR_3DFACE);
        //(HBRUSH)(COLOR_WINDOW+1);
    WindowClass.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYGAME);
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
            case BUTTON_COUNTER:
                {
                    counterIncrease();
                    break;
                }
            case IDM_ABOUT:
                DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_ABOUTBOX), hWindowMain, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWindowMain);
                break;
            default:
                return DefWindowProcW(hWindowMain, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWindowMain, &ps);
             // TODO: Add any drawing code that uses hdc here...
            HPEN hPen = CreatePen(PS_SOLID, 4, RGB(255, 128, 0));
            HPEN oldPen = (HPEN)SelectObject(hdc, hPen);

            Ellipse(hdc, 100, 100, 200, 200); // draws ellipse in window
            SelectObject(hdc, oldPen);
            DeleteObject(hPen);
            EndPaint(hWindowMain, &ps);
        }
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int createButtons(HWND hWindowMain)
{
    button_counter = CreateWindowW(L"button", L"Counter + 1", 
        WS_VISIBLE | WS_CHILD,
        10, 10, 100, 50,
        hWindowMain, BUTTON_COUNTER, NULL, NULL);
    
    return TRUE;
}

int createLabels(HWND hWindowMain)
{
    CreateWindowW(L"static", L"Counter: ",
        WS_CHILD | WS_VISIBLE,
        110, 60, 60, 25,
        hWindowMain, (HMENU) 1, NULL, NULL);

    hDynamicText1 = CreateWindowW(L"static", L"0",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        170, 60, 55, 25,
        hWindowMain, (HMENU) 2, NULL, NULL);

    return TRUE;
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