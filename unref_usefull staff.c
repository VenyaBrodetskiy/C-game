#include "framework.h"

int usefull_staff(HWND hWindowMain) 
{

	// create message box
	MessageBoxW(NULL, L"Here is text", L"Here is title", MB_OK);
	
	// get screen size
	int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
	int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

	// change window position
	SetWindowPos(hWindowMain, NULL, 1, 1, 100, 100, SWP_NOSIZE);
	return 0;
}