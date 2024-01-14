#include "Window.h"
#include <gl/GL.h>

#include <stdio.h>

static ATOM REGISTERED_CLASS = (ATOM)NULL;


LRESULT Wndproc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	Window* w = GetWindowLongPtrW(hWnd, GWLP_USERDATA);

	if (uMsg == WM_KEYDOWN && w->keys[(int)wParam] == 0)
	{
		w->keys[(int)wParam] = 1;
		printf("KEYDOWN %c\n", (char)wParam);

	}

	if (uMsg == WM_KEYUP && w->keys[(int)wParam] == 1)
	{
		w->keys[(int)wParam] = 0;
		printf("KEYUP %c\n", (char)wParam);

	}

	/*switch (uMsg)
	{
	case WM_KEYDOWN:
	{
		
		return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}
	case WM_KEYUP:
	{
		printf("KEYUP %c\n", (char)wParam);
		w->keys[(int)wParam] = 0;
		return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}
	}*/

	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

void registerWindowClass()
{
	if (REGISTERED_CLASS != NULL)return;

	WNDCLASS wndClass = {
		.style = 0,
		.lpfnWndProc = &Wndproc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = NULL,
		.hIcon = NULL,
		.hCursor = NULL,
		.hbrBackground = COLOR_BACKGROUND,
		.lpszMenuName = NULL,
		.lpszClassName = L"WINDOW CLASS NAME"
	};

	REGISTERED_CLASS = (ATOM)RegisterClass(&wndClass);

}

Window* createWindow(const char* title, int width, int height)
{
	registerWindowClass();

	HWND hwnd = CreateWindowExW(
		0,
		REGISTERED_CLASS,
		title,
		WS_TILEDWINDOW,
		100,100,		//X, Y
		width, height,
		NULL,
		NULL,
		NULL,
		NULL
	);

	if (hwnd == NULL)return NULL;

	Window* wnd = memalloc(sizeof(Window));
	if (wnd == NULL)return NULL;

	wnd->ptr = hwnd;
	wnd->height = height;
	wnd->width = width;
	wnd->maxFps = 60;
	wnd->keys = memalloc(sizeof(int) * 255);
	SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)wnd);

	ShowWindow(hwnd, SW_NORMAL);
	initOpenGL(wnd);

	return wnd;
}

int isWindowOpened(Window* wnd)
{
	if (IsWindow(wnd->ptr))return 1;
	return 0;
}

void updateWindow(Window* wnd)
{
	unsigned long long current = highResolutionTimestamp();
	unsigned long long diff = current - wnd->previousUpdateTick;
	while (diff < 1000 / wnd->maxFps)
	{
		current = highResolutionTimestamp();
		diff = current - wnd->previousUpdateTick;
	}
	wnd->previousUpdateTick = current;

	MSG msg;
	if (PeekMessageA(&msg, 0, 0, 0, 1))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

void initOpenGL(Window* window)
{
	HDC context = GetDC(window->ptr);

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), // Size of this structure,
		1, // Structure version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
		32, // Color bits
		8, // R
		0, // R-S
		8, // G
		0, // G-S
		8, // B
		0, // B-S
		8, // A
		0, // A-S
		32, // Accum
		8, 8, 8, 8, // Depth
		24,
		8, // Stencil
		0, // AUX
		PFD_MAIN_PLANE,
		0, // Visible mask
		0 // Damage mask
	};

	int result = ChoosePixelFormat(context, &pfd);
	BOOL ret = SetPixelFormat(context, result, &pfd);
	HGLRC glInstance = wglCreateContext(context);
	HGLRC glInstance2 = wglCreateContext(context);

	ret = wglMakeCurrent(context, glInstance);

	RECT    rcCli;
	GetClientRect(WindowFromDC(context), &rcCli);
	window->width = (float)rcCli.right;
	window->height = (float)rcCli.bottom;
}

void BeginDraw(Window* wnd)
{
	long width = (long)wnd->width;
	long height = (long)wnd->height;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(0.0l, width, height, 0.0l, -1.0l, 1.0l);
	glViewport(0, 0, width, height);
}

void EndDraw(Window* wnd)
{
	HDC dc = GetDC(wnd->ptr);
	SwapBuffers(dc);
	ReleaseDC(wnd->ptr, dc);
}

