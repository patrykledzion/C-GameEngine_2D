#include "Tests.h"
#include "Window.h"
#include "Drawing.h"
#include "Game.h"

int main()
{
	Game* game = malloc(sizeof(Game));
	if (game == NULL)return -1;
	Init(game);
	
	while (isWindowOpened(game->window))
	{
		Update(game);
		Draw(game);
		updateWindow(game->window);	 
	}
	

	return 0;
}