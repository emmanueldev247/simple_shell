#include "main.h"

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
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);

		input = line_read(&read);
		if (read != -1)
		{
			input = remove_comment(input);
			if (input == NULL)
				continue;

			if (check_error(shelldata, input) == -1)
			{
				free(input);
				shelldata->status = 2;
				continue;
			}
			input = str_var(shelldata, input);

			allow = split_cmds(shelldata, input);
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


/**
 * remove_comment - function to remove comment from the shell input
 * @input: input
 *
 * Return: valid command input only (without the comments)
 */
char *remove_comment(char *input)
{
	int i;
	char *result;

	i = 0;
	while (input[i])
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == '\t' || input[i - 1] == ';' || input[i - 1] == ' ')
				break;
		}
		i++;
	}

	if (i)
	{
		result = (char *)malloc(sizeof(char) * (i));
		if (result == NULL)
			return (NULL);

		_memcpy(result, input, i);
		result[i] = '\0';

		free(input);

		return (result);
	}
	return (input);
}

