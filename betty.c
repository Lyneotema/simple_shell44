#include "shell.h"

/**
 * get_input - Read a line of input from the user.
 * @info: A pointer to the info_t structure.
 *
 * Return: The number of characters read.
 */
ssize_t get_input(info_t *info)
{
    ssize_t nread;

    nread = _getline(info, &info->arg, NULL);
    return (nread);
}

/**
 * execute_command - Execute a command entered by the user.
 * @info: A pointer to the info_t structure.
 */
void execute_command(info_t *info)
{
    /* Implement command execution logic here */
    /* You will need to handle creating child processes */
}

/**
 * main - The entry point of the shell program.
 * Return: Always 0.
 */
int main(void)
{
    info_t info = INFO_INIT;
    ssize_t nread;

    do {
        if (isatty(STDIN_FILENO)) {
            _puts("($) ");
        }
        nread = get_input(&info);
        if (nread == -1) {
            _puts("Error reading input\n");
            break;
        }
        if (nread > 1) {
            remove_comments(info.arg);
            execute_command(&info);
        }
    } while (nread != -1);

    free_info(&info, 0);
    return (0);
}

