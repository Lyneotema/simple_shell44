#include "shell.h"

/**
 * _strcpy - Copies a source string to a destination string
 * @dest:  The destination string
 * @src: The source string
 * Return: A pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == NULL)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 * Return: A pointer to the duplicated string
 **/
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - Prints a string to the standard output
 * @str: The string to print
 * Return: Nothing
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - Writes a character to the standard output
 * @c: The character to print
 * Return: 1 upon success, -1 for error (proceed to set errno)
 **/
int _putchar(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}

