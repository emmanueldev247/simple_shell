#include "main.h"

/**
 * handle_sigint - Handle the crtl + c call in terminal
 * @dummy: dummy data to suppress error from signal function signature
 */
void handle_sigint(int dummy)
{
	(void)dummy;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * data_init - initialize the data structure
 * @shelldata: data structure
 * @argv: array of command line arguments
 */
void data_init(shell_state *shelldata, char **argv)
{
	unsigned int i;

	shelldata->arguments = NULL;
	shelldata->argv = argv;
	shelldata->counter = 1;
	shelldata->input = NULL;
	shelldata->status = 0;


	i = 0;
	while (environ[i] != NULL)
		i++;
	shelldata->_environ = (char **)malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
		shelldata->_environ[i] = _strdup(environ[i]);

	shelldata->_environ[i] = NULL;
	shelldata->pid = int_to_str(getpid());
}

/**
 * free_struct - free data strct
 * @shelldata: data structure
 *
 * Return: no return
 */
void free_struct(shell_state *shelldata)
{
	unsigned int i;

	i = 0;
	while (shelldata->_environ[i])
	{
		free(shelldata->_environ[i]);
		i++;
	}

	free(shelldata->pid);
	free(shelldata->_environ);
}

/**
 * main - Entry point
 * @argc: argument count
 * @argv: array of aguments
 *
 * Return: 0 (success), otherwise (failure)
 */
int main(int argc, char **argv)
{
	shell_state shelldata;

	signal(SIGINT, handle_sigint);
	data_init(&shelldata, argv);
	theshell(&shelldata);

	free_struct(&shelldata);
	(void)argc;
	if (shelldata.status > 0)
		return (shelldata.status);

	return (255);
}
