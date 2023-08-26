#ifndef _MAIN_H_
#define _MAIN_H_

#define TOKEN_DELIMITERS "\r\a\n\t "
#define TOKEN_SIZE 128


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>


extern char **environ;

/**
 * struct shdata - structure that contains all relevant data
 *				related to the shell state
 * @arguments: tokens of the command line
 * @argv: array of arguments
 * @counter: lines counte
 * @pid: process identidier of the current shell
 * @_environ: environment variables
 * @input: command line written by the user
 * @status: last status of the shell
 */
typedef struct shdata
{
	char **arguments;
	char **argv;
	int counter;
	char *pid;
	char **_environ;
	char *input;
	int status;
} shell_state;


/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(shell_state *datash);
} builtin_t;

/* aux_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
void print_syntax_error(shell_state *datash, char *input, int i, int bool);


/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, shell_state *datash);
int split_commands(shell_state *datash, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(r_var **h, char *in, shell_state *data);
int check_vars(r_var **h, char *in, char *st, shell_state *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, shell_state *datash);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(shell_state *datash);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(shell_state *datash);
int check_error_cmd(char *dir, shell_state *datash);
int cmd_exec(shell_state *datash);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(shell_state *datash);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, shell_state *datash);
int _setenv(shell_state *datash);
int _unsetenv(shell_state *datash);

/* cd.c */
void cd_dot(shell_state *datash);
void cd_to(shell_state *datash);
void cd_previous(shell_state *datash);
void cd_to_home(shell_state *datash);

/* cd_shell.c */
int cd_shell(shell_state *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(shell_state *datash);

/* _exit.c */
int exit_shell(shell_state *datash);

/* aux_error1.c */
char *strcat_cd(shell_state *, char *, char *, char *);
char *error_get_cd(shell_state *datash);
char *error_not_found(shell_state *datash);
char *error_exit_shell(shell_state *datash);

/* aux_error2.c */
char *error_get_alias(char **arguments);
char *error_env(shell_state *datash);
char *error_syntax(char **arguments);
char *error_permission(char **arguments);
char *error_path_126(shell_state *datash);


/* get_error.c */
int get_error(shell_state *datash, int eval);


/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(shell_state *datash);

/**  mine 88*/


void free_struct(shell_state *shelldata);
void data_init(shell_state *shelldata, char **argv);

/* shell_loop.c */
char *remove_comment(char *input);
void theshell(shell_state *shelldata);
char *line_read(int *eof_status);
int check_error(shell_state *shelldata, char *input);
int first_non_whitespace(char *input, int *i);
int my_isdigit(const char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(char *s1, char *s2);
int compare_str(char *input, const char *delimeter);
char *_strtok(char *input, const char *delimiter);
void revString(char *s);
int getLen(int n);
char *int_to_str(int n);
int my_atoi(char *str);
char *_memcpy(void *dest, const void *src,  unsigned int n);

void handle_sigint(int dummy);

char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdoublep(char **ptr, unsigned int size, unsigned int new_size);

/**  mine 88*/

#endif
