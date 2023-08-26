#include "main.h"

#include "main.h"

/**
 * general_help - help info
 */
void general_help(void)
{
	char *help = "$ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);
}

/**
 * help_only - Help info
 */
void help_only(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);
}

/**
 * help_env - Help info
 */
void help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);
}

/**
 * help_setenv - Help info
 */
void help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);
}

/**
 * help_unsetenv - Help info
 */
void help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);

	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
	fflush(stdout);
}
