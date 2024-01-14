#include "Game.h"
#include "Drawing.h"

#include <stdio.h>

void Init(Game* game)
{
	game->window = createWindow("Skarpety i wisnie twuj stary kisnie", 800, 600);
	game->gameObjectsCount = 1;
	game->gameObjects = memalloc(sizeof(game->gameObjects) * game->gameObjectsCount);
	game->gameObjects[0] = (Player*)malloc(sizeof(Player)); 
	Player* player = game->gameObjects[0];
	if (player == NULL)return -1;
	player->super = createGameObject(5, 5, 50, 50, Color4f(1, 0, 0, 1));
	player->speedX[0] = 0;
	player->speedX[1] = 0;
	player->speedY[0] = 0;
	player->speedY[1] = 0;
	player->maxSpeed = 5;
	player->slide = 0.5;

}

void Update(Game* game)
{
	playerMovement(game);
}

void Draw(Game* game)
{
	BeginDraw(game->window);
	//Draw between here
	for (int i = 0; i < game->gameObjectsCount; i++)
	{
		Player* go = (Player*)game->gameObjects[i];
		DrawRectangle(go->super->x, go->super->y, go->super->w, go->super->h, go->super->color, 1, game->window);
	}
	
	//end here
	EndDraw(game->window);
}

void playerMovement(Game* game)
{
	/*int count = 0;
	for (int i = 0; i < 255; i++)
	{
		if (game->window->keys[i])
		{
			count++;
			printf("%c", (char)i);
		}
	}
	if(count>0)printf("\n");*/

	Player* player = game->gameObjects[0];

	if (game->window->keys['W'] && player->speedY[0] < player->maxSpeed)player->speedY[0] += player->slide;
	if (game->window->keys['S'] && player->speedY[1] < player->maxSpeed)player->speedY[1] += player->slide;
	if (game->window->keys['A'] && player->speedX[0] < player->maxSpeed)player->speedX[0] += player->slide;
	if (game->window->keys['D'] && player->speedX[1] < player->maxSpeed)player->speedX[1] += player->slide;

	if (!game->window->keys['W'] && player->speedY[0] > 0)player->speedY[0] -= player->slide;
	if (!game->window->keys['S'] && player->speedY[1] > 0)player->speedY[1] -= player->slide;
	if (!game->window->keys['A'] && player->speedX[0] > 0)player->speedX[0] -= player->slide;
	if (!game->window->keys['D'] && player->speedX[1] > 0)player->speedX[1] -= player->slide;
	
	if (player->speedX[0] < 0)player->speedX[0] = 0;
	if (player->speedX[1] < 0)player->speedX[1] = 0;
	if (player->speedY[0] < 0)player->speedY[0] = 0;
	if (player->speedY[1] < 0)player->speedY[1] = 0;
 

	player->super->x -= player->speedX[0];
	player->super->x += player->speedX[1];
	player->super->y -= player->speedY[0];
	player->super->y += player->speedY[1];

}
