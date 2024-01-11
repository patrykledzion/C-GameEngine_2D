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