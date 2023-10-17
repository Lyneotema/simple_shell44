#include "shell.h"

/**
 * hsh - Main loop for the shell
 * @info: The info struct to store shell information
 * @av: Argument vector from main()
 *
 * Return: 0 on success, 1 on failure, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t read_status = 0;
	int builtin_ret = 0;

	while (read_status != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_status = get_input(info);
		if (read_status != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_command(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Search for a built-in command
 * @info: The info struct containing shell information
 *
 * Return: -1 if built-in is not found, 0 if built-in executed successfully,
 * 1 if built-in found but not successful, 2 if built-in exits the shell
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
	}
	return (built_in_ret);
}

/**
 * find_command - Find a command in PATH
 * @info: The info struct containing shell information
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *command_path = NULL;
	int i, num_non_delimiters = 0;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			num_non_delimiters++;
	if (!num_non_delimiters)
		return;

	command_path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (command_path)
	{
		info->path = command_path;
		fork_command(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=")
				|| info->argv[0][0] == '/') && is_valid_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "Command not found\n");
		}
	}
}

/**
 * fork_command - Forks an execution thread to run the command
 * @info: The info struct containing shell information
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: Implement error handling function */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: Implement error handling function */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

