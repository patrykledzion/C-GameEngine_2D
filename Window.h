#pragma once

#include <windows.h>
#include "System.h"

struct Window {
	void* ptr;
	int width;
	int height;
}; typedef struct Window Window;

void registerWindowClass();
Window* createWindow(const char *title, int width, int height);
int isWindowOpened(Window* wnd);
void updateWindow(Window* wnd);
void initOpenGL(Window* window);
