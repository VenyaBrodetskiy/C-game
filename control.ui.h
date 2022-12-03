#pragma once

#ifdef GAME_FOR_WIN_API
	// if not WINDOWS, KEYDOWN is not wParam, please make typedef for localKEYDOWN
	#define VK_LEFT		0x25
	#define VK_UP		0x26
	#define VK_RIGHT	0x27
	#define VK_DOWN		0x28
#endif

ControlUI*  initializeControlUI();
void		destructControlUI(ControlUI* controlUI);

