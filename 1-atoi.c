#include "shell.h"

/**
 * is_interactive - Checks if the shell is in interactive mode
 * @info: A structure containing information about the shell
 *
 * Return: 1 if in interactive mode, 0 if in non-interactive mode
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->prompt_char == '>');
}

/**
 * is_delim - Verifies if a character is a delimiter
 * @c: The character to be checked
 * @delim: A string of delimiter characters
 *
 * Return: 1 if the character is a delimiter, 0 if not
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - Checks if a character is alphabetic
 * @c: The character to check
 *
 * Return: 1 if c is an alphabetic character, 0 otherwise
 */
int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converts a string to an integer
 * @s: The string to convert
 *
 * Return: 0 if no numbers are in the string, the converted number otherwise
 */
int _atoi(char *s)
{
	int i, sign = 1, digit_flag = 0, result = 0;

	for (i = 0; s[i] != '\0' && digit_flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			digit_flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (digit_flag == 1)
			digit_flag = 2;
	}

	if (sign == -1)
		return (-result);
	else
		return (result);
}

