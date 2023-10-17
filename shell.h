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


/* _shell_loop.c */
int find_builtin(info_t *);
void find_cmd(info_t *);
int hsh(info_t *, char **);
void fork_cmd(info_t *);

/* parsi_n.c */
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);

/* hsh.c */
int loophsh(char **);

/* _errors.c */
int _eputchar(char);
int _putfd(char c, int fd);
void _eputs(char *);
int _putsfd(char *str, int fd);

/* sstring_g.c */
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcat(char *, char *);

/* string_0.c */
char *_strdup(const char *);
void _puts(char *);
char *_strcpy(char *, char *);
int _putchar(char);

/* exits4.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* token_izer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc4.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* memory4.c */
int bfree(void **);

/* atoi_ic.c */
int is_delim(char, char *);
int _isalpha(int);
int interactive(info_t *);
int _atoi(char *);

/* errors_0.c */
int _erratoi(char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void print_error(info_t *, char *);
void remove_comments(char *);

/* built_in.c */
int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);

/* Built_in0.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* getLine4.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

/* getinfo4.c */
void set_info(info_t *, char **);
void clear_info(info_t *);
void free_info(info_t *, int);

/* _envi_ron.c */
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int populate_env_list(info_t *);

/* getenv4.c */
int _unsetenv(info_t *, char *);
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);

/* history.c */
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int renumber_history(info_t *info);

/* listc4.c */
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
void free_list(list_t **);

/* list4.c */
size_t list_len(const list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);

/* vars4.c */
int is_chain(info_t *, char *, size_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);

#endif
