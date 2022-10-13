#pragma once
#include "framework.h"
#include "main.h"

BOOL InitMainWindow(HINSTANCE, int);
int createButtons(HWND hWindowMain, RECT GameFieldRect);
int createLabels(HWND hWindowMain, RECT GameFieldRect);