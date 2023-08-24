#include "main.h"

/**
 * swapChr - swaps | and & for non-printed chars
 * @input: input string
 * @flag: type of swap
 *
 * Return: swapped string
 */
char *swapChr(char *input, int flag)
{
	int i;

	if (input == NULL)
		return (NULL);

	if (flag == 0)
	{
		i = 0;
		while (input[i])
		{
			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;

				else if (input[i] == '|')
				{
					if (input[i + 1] != '|')
						input[i] = 16;
				}
			}
			i++;
		}
	}
	else
	{
		i = 0;
		while (input[i])
		{
			if (input[i] == 16)
				input[i] = '|';
			else if (input[i] == 12)
				input[i] = '&';
			i++;
		}

	}
	return (input);
}


/**
 * split_cmds - split prompt lines according to the separators
 *				;, | and &, and runs the code
 * @shelldata: shell data
 * @input: input string
 *
 * Return: 0 (exit); 1 (continue)
 */
int split_cmds(shell_state *shelldata, char *input)
{
	int allow;
	SepList *listSep, *headSep;
	lineList *headLine, *listLine;

	headSep = NULL;
	headLine = NULL;

	add_node_list(&headSep, &headLine, input);

	listSep = headSep;
	listLine = headLine;

	while (listLine != NULL)
	{
		shelldata->input = listLine->cmdline;
		shelldata->arguments = split_cmd_line(shelldata->input);
		allow = executeCMD(shelldata);
		free(shelldata->arguments);

		if (allow == 0)
			break;
		(void)listSep;
	/**
	 * here now


		go_next(&listSep, &listLine, shelldata);

		if (listLine != NULL)
			listLine = listLine->next;
	}

	free_sep_list(&headSep);
	free_line_list(&headLine);

	if (allow == 0)
		return (0);
	** here now **/
	}
	return (1);
}


/**
 * split_cmd_line - tokenizes the input string
 * @input: input string.
 *
 * Return: string splitted.
 */
char **split_cmd_line(char *input)
{
	size_t buffer_size;
	char **tokens, *token;
	size_t i;

	buffer_size = TOKEN_SIZE;
	tokens = (char **)malloc(sizeof(char *) * (buffer_size));

	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOKEN_DELIMITERS);
	tokens[0] = token;

	i = 1;
	while (token)
	{
		if (i == buffer_size)
		{
			buffer_size += TOKEN_SIZE;
			tokens = _realloc_doublep(tokens, i, sizeof(char *) * buffer_size);

			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKEN_DELIMITERS);
		tokens[i] = token;
		i++;
	}

	return (tokens);
}
