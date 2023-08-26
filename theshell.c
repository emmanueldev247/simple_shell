#include "main.h"

/**
 * line_read - Read a line of input from stdin
 * @eof_status: A pointer to an integer to store EOF or error status
 *
 * Return: A pointer to the read line or NULL on EOF or error
 */
char *line_read(int *eof_status)
{
	size_t buffer_size = 0;
	char *user_input = NULL;

	*eof_status = getline(&user_input, &buffer_size, stdin);

	return (user_input);
}

/**
 * remove_comment - function to remove comment from the shell input
 * @in: input
 *
 * Return: valid command input only (without the comments)
 */
char *remove_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}


/**
 * theshell - loop of the shell
 * @shelldata: data structure containing shell data
 *
 * Return: nothing
 */
void theshell(shell_state *shelldata)
{
	int allow, read;
	char *input = NULL;

	allow = 1;
	while (allow == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		fflush(stdout);

		input = line_read(&read);
		if (read != -1)
		{
			input = remove_comment(input);
			if (input == NULL)
				continue;

			if (check_error(shelldata, input) == 1)
			{
				free(input);
				shelldata->status = 2;
				continue;
			}
			input = rep_var(input, shelldata);

			allow = split_commands(shelldata, input);
			shelldata->counter += 1;
			free(input);
		}
		else
		{
			free(input);
			allow = 0;
		}
	}
}
