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

#endif
