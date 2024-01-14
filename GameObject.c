#include "GameObject.h"

GameObject_t* createGameObject(int x, int y, int w, int h, Color4_t* color)
{
	GameObject_t *ret = memalloc(sizeof(GameObject_t));

	ret->x = x;
	ret->y = y;
	ret->w = w;
	ret->h = h;
	ret->color = color;

	return ret;

}
