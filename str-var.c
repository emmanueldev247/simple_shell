#include "main.h"

/**
 * str_var - functions to replace string into vars
 * @input: input string
 * @shelldata: data structure
 *
 * Return: returns replaced string
 */
char *str_var(char *input, shell_state *shelldata)
{
	int olen, nlen;
	char *status, *new_input;
	s_var *head, *indx;

	head = NULL;
	status = int_to_str(shelldata->status);

/*	olen = check_vars(&head, input, status, shelldata);*/

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	nlen = 0;
	indx = head;

	for (; indx != NULL; indx = indx->next)
		nlen += (indx->valLen - indx->varLen);

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

/*  new_input = replaced_input(&head, input, new_input, nlen); */

	free(status);
	free(input);
	free_rvar_list(&head);

	return (new_input);
}


	/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvar_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

