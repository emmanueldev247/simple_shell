#include "main.h"

/**
 * str_var - functions to replace string into vars
 * @input: input string
 * @shelldata: data structure
 *
 * Return: returns replaced string
 */
char *str_var(shell_state *shelldata, char *input)
{
	int olen, nlen;
	char *status, *new_input;
	s_var *head, *index;

	head = NULL;
	status = int_to_str(shelldata->status);

	olen = varCheck(&head, input, status, shelldata);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	nlen = 0;
	index = head;

	for (; index != NULL; index = index->next)
		nlen += (index->valLen - index->varLen);

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(status);
	free(input);
	free_svar_list(&head);

	return (new_input);
}

/**
 * varCheck - check if the typed variable is $$ or $?
 * @head: head of the linked list
 * @in: input string
 * @status: last status of the shell
 * @shelldata: data structure
 *
 * Return: no return
 */
int varCheck(s_var **head, char *in, char *status, shell_state *shelldata)
{
	int i, lst, lpd;

	lpd = _strlen(shelldata->pid);
	lst = _strlen(status);

	i = 0;
	while (in[i])
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_svar_node(head, status, 2, lst), i++;
			else if (in[i + 1] == '$')
				add_svar_node(head, shelldata->pid, 2, lpd), i++;
			else if (in[i + 1] == '\n')
				add_svar_node(head, NULL, 0, 0);
			else if (in[i + 1] == '\0')
				add_svar_node(head, NULL, 0, 0);
			else if (in[i + 1] == ' ')
				add_svar_node(head, NULL, 0, 0);
			else if (in[i + 1] == '\t')
				add_svar_node(head, NULL, 0, 0);
			else if (in[i + 1] == ';')
				add_svar_node(head, NULL, 0, 0);
			else
				envCheck(head, shelldata, in + i);
		}
		i++;
	}

	return (i);
}

/**
 * envCheck - checks if the typed variable is an env
 * @head: head of linked list
 * @shelldata: data structure
 * @in: input string
 *
 * Return: no return
 */
void envCheck(s_var **head, shell_state *shelldata, char *in)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = shelldata->_environ;

	row = 0;

	while (_envr[row])
	{
		j = 1;
		chr = 0;

		while (_envr[row][chr])
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_svar_node(head, _envr[row] + chr + 1, j, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
			chr++;
		}
		row++;
	}

	j = 0;
	while (in[j])
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
		j++;
	}

	add_svar_node(head, NULL, j, 0);
}
/**
 * replaced_input - replaces string into variables
 * @head: head of the linked list
 * @input: input string
 * @new_input: replaced input string
 * @nlen: new length
 *
 * Return: replaced string
 */
char *replaced_input(s_var **head, char *input, char *new_input, int nlen)
{
	int  i, j, k;
	s_var *index;

	index = *head, i = 0, j = 0;
	while (i < nlen)
	{
		if (input[j] == '$')
		{
			if (index->varLen && !(index->valLen))
			{
				k = 0;
				while (k < (index->varLen))
				{
					j++, k++;
				}
				i--;
			}
			else if (!(index->varLen) && !(index->valLen))
			{
				new_input[i] = input[j];
				i++, j++;
			} else
			{
				k = 0;
				while (k < index->valLen)
				{
					new_input[i] = index->varVal[k];
					i++, k++;
				}
				j += (index->varLen), i--;
			}
			index = index->next;
		}
		else
		{
			new_input[i] = input[j];
			i++, j++;
		}
	}
	return (new_input);
}
