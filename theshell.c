#include "main.h"

/**
 * theshell - loop of the shell
 * @shelldata: data structure containing shell data
 *
 * Return: nothing
 */
void theshell(shell_state *shelldata)
{
	int allow;
	char *input = NULL;
	size_t len = 0;
	ssize_t read;

	allow = 1;
	while (allow)
	{
		write(STDOUT_FILENO, ">_> ", 4);
		fflush(stdout);

		read = getline(&input, &len, stdin);
		if (read != -1)
		{
			input = remove_comment(input);
			if (input == NULL)
				continue;

			if (check_error(shelldata, input) == 1)
			{
				free(input);
				shelldata->status = 2;
			/*here*/
			}
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
	int i, here;
	int len = _strlenV2(input);
	char *result;

	here = 0;
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
			{
				here = i;
				break;
			}
		}
		i++;
	}

	if (here)
	{
		result = (char *)malloc(sizeof(char) * (here));
		if (result == NULL)
			return (NULL);

		memcpy(result, input, here);
		result[here] = '\0';

		free(input);

		return (result);
	}
	return (input);
}

