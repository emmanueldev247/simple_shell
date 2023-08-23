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

extern char **environ;


/**
 * struct data - structure that contains all relevant data
 *				related to the shell state
 * @arguments: tokens of the command line
 * @argv: array of arguments
 * @counter: lines counte
 * @pid: process identidier of the current shell
 * @_environ: environment variables
 * @input: command line written by the user
 * @status: last status of the shell
 */
typedef struct data
{
	char **arguments;
	char **argv;
	int counter;
	char *pid;
	char **_environ;
	char **input;
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
char *construct_err(shell_state *shdata, char *i, char *m1, char *m2, char *m3);
void print_error_message(char *error_message);
char *determine_error_message(char *input, int i, int bool);
int error_sep(char *input, int i, char last);
int xRepeatedChar(char *input, int i);
char *str_var(char *input, shell_state *shelldata);

#endif
