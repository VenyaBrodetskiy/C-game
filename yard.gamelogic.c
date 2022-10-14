#include "yard.gamelogic.h"

extern char FieldMap[1920][1080];

int initYard(RECT GameFieldRect) 
{
	for (int x = 0; x <= GameFieldRect.right; x++) {
		for (int y = 0; y <= GameFieldRect.bottom; y++) {
			FieldMap[x][y] = EMPTY;
		}
	}

	// build walls
	for (int x = 0; x <= GameFieldRect.right; x++) {
		FieldMap[x][0] = WALL;
	}
	for (int x = 0; x <= GameFieldRect.right; x++) {
		FieldMap[x][GameFieldRect.bottom + 1] = WALL;
	}
	for (int y = 0; y <= GameFieldRect.bottom; y++) {
		FieldMap[0][y] = WALL;
	}
	for (int y = 0; y <= GameFieldRect.bottom; y++) {
		FieldMap[GameFieldRect.right + 1][y] = WALL;
	}
}