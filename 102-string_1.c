#include "shell.h"

/**
 * string_length - Calculate the length of a string.
 * @s: The string to determine the length of.
 *
 * Return: The length of the string.
 */
int string_length(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;

	return (length);
}

/**
 * string_compare - Compare two strings in alphabetical order.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return:
 * - 0 if s1 is equal to s2.
 * - A positive value if s1 is greater than s2.
 * - A negative value if s1 is less than s2.
 */
int string_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Check if one string starts with another.
 * @haystack: The string to check.
 * @needle: The substring to look for.
 *
 * Return:
 * - Address of the character in haystack after the common prefix.
 * - NULL if the needle is not found at the beginning of the haystack.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}

	return ((char *)haystack);
}

/**
 * string_concatenate - Concatenate two strings.
 * @dest: The destination buffer to which the source is concatenated.
 * @src: The source buffer to be concatenated.
 *
 * Return: A pointer to the destination buffer.
 */
char *string_concatenate(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;

	return (result);
}

