#pragma once

#include <windows.h>
#include "System.h"

struct Window {
	void* ptr;
	int width;
	int height;
	int maxFps;
	unsigned long long framesPerformanceStart;
	unsigned long long framesRendered;
	unsigned long long previousUpdateTick;
	int* keys;
	
}; typedef struct Window Window;

void registerWindowClass();
Window* createWindow(const char *title, int width, int height);
int isWindowOpened(Window* wnd);
void updateWindow(Window* wnd);
void initOpenGL(Window* window);
void BeginDraw(Window* wnd);
void EndDraw(Window* wnd);