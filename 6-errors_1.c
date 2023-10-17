#include "shell.h"

/**
 * _erratoi - Convert a string to an integer with error handling
 * @s: The string to convert
 * Return: The converted integer if successful, -1 on error
 */
int _erratoi(char *s)
{
	int result = 0;
	unsigned long int value = 0;

	if (*s == '+')
		s++;

	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			value *= 10;
			value += (s[i] - '0');
			if (value > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (value);
}

/**
 * print_error - Print an error message
 * @info: The info struct for the given parameters
 * @estr: The error string
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Print an integer in base 10
 * @input: The integer to print
 * @fd: The file descriptor to write to
 * Return: The total number of characters printed
 */
int print_d(int input, int fd)
{
	int (*print_func)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		print_func = _eputchar;
	if (input < 0)
	{
		absolute = -input;
		print_func('-');
		count++;
	}
	else
		absolute = input;
	current = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			print_func('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_func('0' + current);
	count++;
	return (count);
}

/**
 * convert_number - Convert a number to a string representation.
 * @num: The number to convert
 * @base: The base for conversion
 * @flags: Flags for formatting
 * Return: The string representation of the number
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Replace the first instance of '#' with '\0' in the string
 * @buf: The string to modify
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
	}
}

