#include "shell.h"
/**
 **_strncpy - cp. string
 *@dest: The Destination to cp String into
 *@src: Source String
 *
 *@n: No. of chars to be Copied
 *Return: Concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int z, j;
	char *s = dest;

	z = 0;
	while (src[z] != '\0' && z < n - 1)
	{
		dest[z] = src[z];
		z++;
	}
	if (z < n)
	{
		j = z;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - Concatenates 2 strings
 *@dest: 1st. String.
 *@src: 2nd. String.
 *@n: No. of Bytes to Maximally use
 *Return: Concatenated String
 */
char *_strncat(char *dest, char *src, int n)
{
	int z, j;
	char *s = dest;

	z = 0;
	j = 0;
	while (dest[z] != '\0')
		z++;
	while (src[j] != '\0' && j < n)
	{
		dest[z] = src[j];
		z++;
		j++;
	}
	if (j < n)
		dest[z] = '\0';
	return (s);
}

/**
 **_strchr - Finds A char in String.
 *@s: String to Pass.
 *@c: Char being looked For.
 *Return: (s) Pointer to mem. area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
