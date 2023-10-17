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


/* 100-shell_loop.c */
int find_builtin(info_t *info);
void find_command(info_t *info);
int hsh(info_t *info, char **av);
void fork_command(info_t *info);

/* 7-parser.c */
char *duplicate_chars(char *path, int start, int stop);
int is_command(info_t *info, char *path);
char *find_command_in_path(info_t *info, char *path_str, char *command);

/* hsh.c */
int loophsh(char **);

/* 5-errors.c */
int _eputchar(char c);
int _putfd(char c, int fd);
void _eputs(char *str);
int _putsfd(char *str, int fd);

/* 102-string_1.c */
int string_compare(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
int string_length(char *s);
char *string_concatenate(char *dest, char *src);

/* 101-string.c */
char *_strdup(const char *str);
void _puts(char *str);
char *_strcpy(char *dest, char *src);
int _putchar(char c);

/* exits4.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* 8-tokenizer.c */
char **strtow(char *str, char *delimiters);


/* realloc4.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* memory4.c */
int bfree(void **);

/* 1-atoic.c */
int is_delim(char c, char *delim);
int _isalpha(int c);
int is_interactive(info_t *info);
int _atoi(char *s);

/* 6-errors_1.c */
int _erratoi(char *s);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void print_error(info_t *info, char *estr);
void remove_comments(char *buf);

/* 2-builtin.c */
int _mycd(info_t *info);
int _myexit(info_t *info);
int _myhelp(info_t *info);

/* 3-builtin_1.c */
int _myhistory(info_t *info);
int _myalias(info_t *info);
int print_alias(list_t *node);
int set_alias(info_t *info, char *str);
int unset_alias(info_t *info, char *str);

/* getLine4.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

/* getinfo4.c */
void set_info(info_t *, char **);
void clear_info(info_t *);
void free_info(info_t *, int);

/* 4-environ.c */
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _myenv(info_t *info);
int populate_env_list(info_t *info);

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


