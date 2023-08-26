#include "main.h"

/**
 * help_cmd - function that diplay help messages
 * @shelldata: data structure
 *
 * Return: Return 1
 */
int help_cmd(shell_state *shelldata)
{
	if (shelldata->arguments[1] == 0)
		general_help();

	else if (_strcmp(shelldata->arguments[1], "help") == 0)
		help_only();

	else if (_strcmp(shelldata->arguments[1], "env") == 0)
		help_env();

	else if (_strcmp(shelldata->arguments[1], "setenv") == 0)
		help_setenv();

	else if (_strcmp(shelldata->arguments[1], "alias") == 0)
		help_alias();

	else if (_strcmp(shelldata->arguments[1], "unsetenv") == 0)
		help_unsetenv();

	else if (_strcmp(shelldata->arguments[1], "cd") == 0)
		help_cd();

	else if (_strcmp(shelldata->arguments[1], "exit") == 0)
		help_exit();

	else
	{
		write(STDERR_FILENO, shelldata->arguments[0],
		      _strlen(shelldata->arguments[0]));
		fflush(stdout);
	}

	shelldata->status = 0;
	return (1);
}

/**
 * help_alias - Help info
 */
void help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "\tDefine or display aliases.\n";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);
}

/**
 * help_cd - Help info
 */
void help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);
}

/**
 * help_exit - Help info
 */
void help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);
}
