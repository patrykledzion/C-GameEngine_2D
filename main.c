#include "Tests.h"
#include "Window.h"


int main()
{
	Window* wnd = createWindow("Okno testowe", 800, 600);

	while (isWindowOpened(wnd))
	{
		updateWindow(wnd);
	}

	return 0;
}