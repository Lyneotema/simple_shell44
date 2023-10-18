#ifndef SHELL_H_
#define SHELL_H_
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

/* this is for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* this is for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* this is for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - The singly linked list
 * @num: no. field
 * @str: The string.
 * @next: Pointer to next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
	} list_t;

/**
 * struct passinfo - Has pseudo-arg. to pass into a func.,
 * allowing uniform prototype for func. address struct
 * @arg: String gotten from getline having args.
 * @argv: The array of strings gotten from arg
 * @path: a string path for the current command
 * @argc: Argument number
 * @line_count: Error number.
 * @err_num: Error code for exit()s.
 * @linecount_flag: if on number this line of input
 * @fname: filename of program
 * @env: The Linked list local cp of environ.
 * @environ: Tailored modified cp of environ from LL env
 * @history: Node for history
 * @alias: Node for alias
 * @env_changed: On if environ was altered
 * @status: the last executable command return status
 * @cmd_buf: Pointer of address to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: Where to read line input from fd
 * @histcount: History line no. count
 */
typedef struct passinfo
{
	char *arg;
        size_t arg_len;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* address to cmd ; chain buffer, for memory mngt. */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Has a builtin string & related function
 * @type: Builtin command flag
 * @func: Func. (function)
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* betty.c */
ssize_t get_input(info_t *info);
void execute_command(info_t *info);
int main(void);




#endif
