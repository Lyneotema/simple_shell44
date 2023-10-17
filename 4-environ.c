#include "shell.h"

/**
 * _myenv - Prints the current environment.
 * @info: A structure containing arguments and ensuring consistent prototypes.
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Fetches the value of an environment variable.
 * @info: A structure containing arguments and ensuring consistent prototypes.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable or NULL if not found.
 **/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Sets a new environment variable or alters an existing variable.
 * @info: A structure containing arguments and ensuring consistent prototypes.
 * Return: 0 if successful, 1 if an incorrect number of arguments.
 **/
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Eradicates an environment variable.
 * @info: A structure containing arguments and ensuring consistent prototypes.
 * Return: Always 0.
 **/
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates linked list from the environ array.
 * @info: structure containing arguments and function prototypes.
 * Return: Always 0.
 **/
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
