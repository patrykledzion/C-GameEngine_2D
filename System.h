#pragma once

#include <Windows.h>

//MEMORY ALLOCATION
void* memalloc(int size);
void memfree(void* mem);
void* memrealloc(void* mem, int size);