#pragma once

#include "System.h"

struct GameObject_t {
	int x;
	int y;
	int w;
	int h;
	Color4_t* color;
}; typedef struct GameObject_t GameObject_t;

GameObject_t* createGameObject(int x, int y, int w, int h, Color4_t* color);