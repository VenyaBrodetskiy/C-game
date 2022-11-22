#pragma once

#include "resource.h"
#include "framework.h"

#pragma comment(lib, "comctl32")

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    MainWindowProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

