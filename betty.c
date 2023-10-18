#include "shell.h"

/**
 * get_input - Read a line of input from the user.
 * @info: A pointer to the info_t structure.
 *
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t get_input(info_t *info)
{
    ssize_t nread;

    nread = getline(&info->arg, &info->arg_len, stdin);
    if (nread == -1) {
        perror("Error reading input");
    }

    return nread;
}

/**
 * execute_command - Execute a command entered by the user.
 * @info: A pointer to the info_t structure.
 */
void execute_command(info_t *info)
{
    /* Implement command execution logic here */
    /* You will need to handle creating child processes */
    // Example:
    // pid_t child_pid = fork();
    // if (child_pid == -1) {
    //     perror("Fork failed");
    //     exit(EXIT_FAILURE);
    // } else if (child_pid == 0) {
    //     // Child process code
    //     // Execute the command using execvp, for example
    //     // Example: execvp(info->arg[0], info->arg);
    //     perror("Command execution failed");
    //     exit(EXIT_FAILURE);
    // } else {
    //     // Parent process code (you may need to wait for the child)
    // }
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
            // Remove trailing newline character
            if (info.arg[nread - 1] == '\n') {
                info.arg[nread - 1] = '\0';
            }
            // You may want to tokenize the input for command handling
            execute_command(&info);
        }
    } while (nread != -1);

    free_info(&info, 0);
    return (0);
}


