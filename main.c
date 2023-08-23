#include "main.h"

/**
 * main - Entry point
 * @argc: argument count
 * @argv: array of aguments
 * @env: environmental variable
 *
 * Return: 0 (success), otherwise (faailure)
 */
int main(int argc, char **argv, char **env)
{
	shell_state shelldata;

	signal(SIGINT, handle_sigint);
	data_init(&shelldata, argv);
	theshell(&shelldata);

	/** here **/
	if (shelldata.status < 0)
		return (255);

	return (shelldata.status);
}

/**
 * handle_sigint - Handle the crtl + c call in terminal
 * @dummy: dummy data to suppress error from signal function signature
 */
void handle_sigint(int dummy)
{
	write(STDOUT_FILENO, "\n>_> ", 5);
	fflush(stdout);
	(void)dummy;
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
	shelldata->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
		shelldata->_environ[i] = _strdup(environ[i]);

	shelldata->_environ[i] = NULL;
	shelldata->pid = int_to_str(getpid());
}
