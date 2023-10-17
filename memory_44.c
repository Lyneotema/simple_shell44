#include "shell.h"
/**
 * bfree - Free address and NULLs the pointer
 * @ptr: Pointer to the address to be freed.
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

