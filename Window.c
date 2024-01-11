#include "Window.h"

static ATOM REGISTERED_CLASS = (ATOM)NULL;


LRESULT Wndproc(
	HWND unnamedParam1,
	UINT unnamedParam2,
	WPARAM unnamedParam3,
	LPARAM unnamedParam4
)
{
	return DefWindowProcA(unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4);
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

	SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)wnd);

	ShowWindow(hwnd, SW_NORMAL);

	return wnd;
}

int isWindowOpened(Window* wnd)
{
	if (IsWindow(wnd->ptr))return 1;
	return 0;
}

void updateWindow(Window* wnd)
{
	MSG msg;
	if (PeekMessageA(&msg, 0, 0, 0, 1))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

void initOpenGL(Window* window)
{

}

