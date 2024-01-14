#pragma once

#include "Window.h"
#include "GameObject.h"

struct Game {
	Window* window;
	void** gameObjects;
	int gameObjectsCount;
}; typedef struct Game Game;

void Init(Game* game);
void Update(Game* game);
void Draw(Game* game);


struct Player {
	GameObject_t* super;
	float speedX[2];
	float speedY[2];
	float maxSpeed;
	float slide;
}; typedef struct Player Player;

void playerMovement(Game* game);