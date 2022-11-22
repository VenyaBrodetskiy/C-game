#pragma once
#include <windows.h>

enum Buttons {
    BUTTON_START,
    BUTTON_PAUSE,
    STATIC_TEXT1,
    DYNAMIC_TEXT1,
    GROUP_BOX1,
    RADIO_WALLS,
    RADIO_NOWALLS,
    SPEED_LABEL,
    TRACK_BAR,
    STATIC_TEXT2,
    STATIC_TEXT3,
    PROGRESS_BAR
};

BOOL InitMainWindow(HINSTANCE hInstance, int nCmdShow, RECT PlayGroundInPixels);
int createButtons(HWND hWindowMain, RECT PlayGroundInPixels);
