#include "shell.h"

/**
 * is_command - Check if a file is an executable command
 * @info: Pointer to the info struct
 * @path: File path to check
 *
 * Return: 1 if the file is an executable command, 0 otherwise
 **/
int is_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - Duplicate a range of characters from a string
 * @path_str: The source string
 * @start: Index of the starting character
 * @stop: Index of the stopping character
 *
 * Return: Pointer to the new buffer
 */
char *duplicate_chars(char *path_str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			buf[k++] = path_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_command_in_path - Find a command in the PATH string
 * @info: Pointer to the info struct
 * @path_str: The PATH string
 * @command: The command to locate
 *
 * Return: Pointer to the path of the command if found, or NULL
 */
char *find_command_in_path(info_t *info, char *path_str, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_command(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = duplicate_chars(path_str, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_command(info, path))
				return (path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

