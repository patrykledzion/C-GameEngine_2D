#pragma once

#include <Windows.h>

struct Vector3 {
	int x;
	int y;
	int z;
}; typedef struct Vector3 Vector3;

struct Color4_t {
	float r;
	float g;
	float b;
	float a;
}; typedef struct Color4_t Color4_t;

//MEMORY ALLOCATION
void* memalloc(int size);
void memfree(void* mem);
void* memrealloc(void* mem, int size);
unsigned long long highResolutionTimestamp();

Color4_t* Color4f(float r, float g, float b, float a);