#pragma once
#include "main.h"

#define MAX_LOADSTRING 100

// button start sizes
#define BUTTON_WIDTH 100 // Width of right-side menu
#define BUTTON_HEIGHT 35

// static text sizes
#define STAT_TEXT_X 55
#define STAT_TEXT_Y 25

// dynamic text sizes
#define DYN_TEXT_X 45
#define DYN_TEXT_Y 25

// indent
#define SPACE_PIXEL 2

// group box with radio buttons
#define GROUP_BOX_HEIGHT 80
#define RADIO_BTN_WIDTH 95
#define RADIO_BTN_HEIGHT 25

// trackbar 
#define TRACKBAR_Y 150
#define TRACKBAR_HEIGHT 30
#define TB_LABEL_W 35
#define TB_LABEL_H 20
#define TB_RIGHT_LABEL_POS 70
#define TB_TIC_FREQ (SPEED_MIN - SPEED_MAX) / 2 // Calculated trackbar tic frequency 
#define TB_DEFAULT_VALUE (SPEED_MIN + SPEED_MAX) / 2 // Calculated average of min and max speed

// tips
#define TIPS_Y 300
#define TIPS_WIDTH 100
#define TIPS_HEIGHT 100

// progress bar
#define PB_LABEL_H 20