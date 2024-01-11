#include "Tests.h"

int TEST_MEM_ALLOC()
{
	//Test memory allocation
	int* array_int = memalloc(sizeof(int) * 2137);
	if (array_int == NULL)return MEM_ALLOC_ERROR;

	char* array_char = memalloc(sizeof(int) * 69);
	if (array_char == NULL)return MEM_ALLOC_ERROR;

	*array_int = 2137;
	*array_char = 69;

	int INT_VAR = *array_int;
	char CHAR_VAR = *array_char;

	//Test memory reallocation
	int* new_arr_int = memrealloc(array_int, sizeof(int) * (2138));
	if (new_arr_int == NULL)return MEM_REALLOC_ERROR;
	array_int = new_arr_int;
	if (array_int[2137] != 0)return MEM_REALLOC_ERROR;

	//Test memory free
	memfree(array_int);
	memfree(array_char);

	if (*array_int == 2137)return MEM_FREE_ERROR;
	if (*array_char == 69)return MEM_FREE_ERROR;



	return 0;
}
