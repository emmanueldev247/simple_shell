#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>

#define TOKEN_SIZE 128
#define BUFFER_SIZE 1024
#define TOKEN_DELIMITERS "\r\a\n\t "

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
 * struct str_var_list - linked list for str_var
 * @valLen: length of the value
 * @varLen: length of the variable
 * @varVal: value of the variable
 * @next: next node in list
 */
typedef struct str_var_list
{
	int valLen;
	int varLen;
	char *varVal;
	struct str_var_list *next;
} s_var;

/**
 * struct list_line - singly linked list
 * @cmdline: command line
 * @next: next node
 *
 */
typedef struct list_line
{
	char *cmdline;
	struct list_line *next;
} lineList;


/**
 * struct list_sep - singly linked list
 * @sep: seperators
 * @next: next node
 *
 */
typedef struct list_sep
{
	char sep;
	struct list_sep *next;
} SepList;

/**
 * struct cmd_builtin_srt - struct for command arguments
 * @name: The name of the command builtin i.e cd, etc
 * @func: pointer function
 */
typedef struct cmd_builtin_srt
{
	char *name;
	int (*func)(shell_state *shelldata);
} builtin_list;




int main(int ac, char **av, char **env);
void handle_sigint(int dummy);
void data_init(shell_state *shelldata, char **argv);
char *_strdup(const char *str);
int _strlen(const char *s);
int _strlenV2(char *s);
char *_memcpy(void *dest, const void *src,  unsigned int n);
char *_memcpyV2(char *dest, char *src, int n);
int getLen(int n);
char *int_to_str(int n);
void theshell(shell_state *shelldata);
char *remove_comment(char *in);
int first_non_whitespace(char *input, int *index);
int check_error(shell_state *shelldata, char *input);
void print_error(shell_state *shelldata, char *input, int i, int bool);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
void print_error(shell_state *shelldata, char *input, int i, int bool);
char *cnstr_err(shell_state *shdata, char *i, char *m1, char *m2, char *m3);
void print_error_message(char *error_message);
char *determine_error_message(char *input, int i, int bool);
int error_sep(char *input, int i, char last);
int xRepeatedChar(char *input, int i);
char *str_var(shell_state *shelldata, char *input);
int varCheck(s_var **head, char *in, char *status, shell_state *shelldata);
void envCheck(s_var **head, shell_state *shelldata, char *in);
s_var *add_svar_node(s_var **head, char *val, int lvar, int lval);
void free_svar_list(s_var **head);
char *replaced_input(s_var **head, char *input, char *new_input, int nlen);
int split_cmds(shell_state *shelldata, char *input);
char *swapChr(char *input, int flag);
void add_node_list(SepList **headSep, lineList **headList, char *input);
SepList *add_sep_node(SepList **head, char sep);
lineList *add_line_node(lineList **head, char *cmdline);
int compare_str(char *input, const char *delimeter);
char *_strtok(char *input, const char *delimiter);
void free_sep_list(SepList **head);
void free_line_list(lineList **head);
int split_cmds(shell_state *shelldata, char *input);
char **split_cmd_line(char *input);
char **_realloc_doublep(char **ptr, unsigned int size, unsigned int new_size);
int executeCMD(shell_state *datash);

int (*getBuiltin(char *cmd))(shell_state *);

int _strcmp(char *s1, char *s2);
void setEnv(char *env_name, char *env_value, shell_state *shelldata);
char *copyInfo(char *env_name, char *env_value);
int cmp_setenv(shell_state *shelldata);
int unset_env(shell_state *shelldata);

int cd_cmd(shell_state *shelldata);
void cd_to_dot(shell_state *shelldata);
void cd_here(shell_state *shelldata);
void cd_to_previous(shell_state *shelldata);
void cd_home(shell_state *shelldata);

char *get_env(const char *var_name, char **_env);
void revString(char *s);
int cmp_env(const char *nenv, const char *name);

int getError(shell_state *shelldata, int eval);
char *errorEnv(shell_state *shelldata);
char *err_not_found(shell_state *shelldata);
char *error_on_path126(shell_state *shelldata);
char *err_exit(shell_state *shelldata);
char *error_cd(shell_state *shelldata);
char *err_strcat(shell_state *sh, char *msg, char *error, char *ver_str);

#endif
