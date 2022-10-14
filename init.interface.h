#pragma once
#include "framework.h"
#include "main.h"

BOOL InitMainWindow(HINSTANCE hInstance, int nCmdShow, RECT PlayGroundInPixels);
int createButtons(HWND hWindowMain, RECT PlayGroundInPixels);
int createLabels(HWND hWindowMain, RECT PlayGroundInPixels);