#include "shell.h"

/**
 * _exit_shell - Exit the shell
 * @info: Structure containing arguments and status
 * Return: 0 on success, 1 if an error occurred
 */
int _exit_shell(info_t *info)
{
    int exit_status;

    if (info->argc > 1)
    {
        exit_status = _atoi(info->argv[1]);
        if (exit_status == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return (1);
        }
        info->err_num = exit_status;
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * _change_directory - Change the current working directory
 * @info: Structure containing arguments and status
 * Return: Always 0
 */
int _change_directory(info_t *info)
{
    char *current_dir, *new_dir, buffer[1024];
    int chdir_result;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        _puts("TODO: >>getcwd failure message here<<\n");
    if (!info->argv[1])
    {
        new_dir = _getenv(info, "HOME=");
        if (!new_dir)
            chdir_result = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
        else
            chdir_result = chdir(new_dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(current_dir);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');
        chdir_result = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
    }
    else
    {
        chdir_result = chdir(info->argv[1]);
    }
    if (chdir_result == -1)
    {
        print_error(info, "can't change directory to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * _help_shell - Display help message
 * @info: Structure containing arguments and status
 * Return: Always 0
 */
int _help_shell(info_t *info)
{
    char **arguments;

    arguments = info->argv;
    _puts("Help: Function to be implemented\n");
    if (0)
        _puts(*arguments); /* Temporary unused workaround */
    return (0);
}

