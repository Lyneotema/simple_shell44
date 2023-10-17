#include "shell.h"
/**
 * _memset - Loads up memory with a constant Byte.
 * @s: Memory area address
 * @b: The byte to load up pointer to s with
 * @n: Amount of bytes to be loaded up
 * Return: (s) an address to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Frees a String of Strings.
 * @pp: The String of Strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Reallocates a memory block
 * @ptr: Address to prev. malloc'ated block
 * @old_size: Byte size of the prev. block
 * @new_size: The new block byte size
 * Return: Adrress of the old block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

