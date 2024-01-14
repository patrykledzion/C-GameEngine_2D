#include "System.h"

void* memalloc(int size)
{
	return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (SIZE_T)size);
}

void memfree(void* mem)
{
	HeapFree(GetProcessHeap(), 0, mem);
}

void* memrealloc(void* mem, int size)
{
	return HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, mem, (SIZE_T)size);
}

Color4_t* Color4f(float r, float g, float b, float a)
{
	Color4_t *ret = memalloc(sizeof(Color4_t));
	ret->r = r;
	ret->g = g;
	ret->b = b;
	ret->a = a;

	return ret;
}

unsigned long long highResolutionTimestamp() // ms timestamp
{
	LARGE_INTEGER li;
	LARGE_INTEGER fq;

	QueryPerformanceFrequency(&fq);
	QueryPerformanceCounter(&li);

	li.QuadPart *= 1000;
	li.QuadPart /= fq.QuadPart;

	return li.QuadPart;
}