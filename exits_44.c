#include "shell.h"
/**
 **_strncpy - cp. string
 *@dest: The destination to cp string to
 *@src: Source String
 *@n: the no. of chars to be copied
 *Return: Concatenated String
 */
char *_strncpy(char *dest, char *src, int n)
{
	int m, j;
	char *s = dest;

	m = 0;
	while (src[m] != '\0' && m < n - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < n)
	{
		j = m;
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
 *@dest: 1st. String
 *@src: 2nd. String
 *@n: no. of bytes to maximally use
 *Return: Concatenated String
 */
char *_strncat(char *dest, char *src, int n)
{
	int m, j;
	char *s = dest;

	m = 0;
	j = 0;
	while (dest[m] != '\0')
		m++;
	while (src[j] != '\0' && j < n)
	{
		dest[m] = src[j];
		m++;
		j++;
	}
	if (j < n)
		dest[m] = '\0';
	return (s);
}

/**
 **_strchr - Finds a char in string
 *@s: the string to pass.
 *@c: Char being looked for
 *Return: (s) an address to mem. area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
