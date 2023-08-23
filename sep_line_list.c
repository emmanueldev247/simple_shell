#include "main.h"

/**
 * add_sep_node - adds a separator at the end of a SepList
 * @head: head of the linked list
 * @sep: separator
 *
 * Return: address of the head
 */
SepList *add_sep_node(SepList **head, char sep)
{
	SepList *new, *temp;

	new = malloc(sizeof(SepList));
	if (new == NULL)
		return (NULL);

	new->sep = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
		*head = new;
	else
	{
		for (; temp->next != NULL; temp = temp->next)
			;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_sep_list - frees a SepList
 * @head: head of the linked list
 *
 */
void free_sep_list(SepList **head)
{
	SepList *temp, *current;

	if (head)
	{
		for (current = *head; current != NULL; current = temp)
		{
			temp = current->next;
			free(current);
		}
		*head = NULL;
	}
}


/**
 * add_line_node - adds a command line at the end of a lineList
 * @head: head of the linked list
 * @cmdline: command line to be added
 *
 * Return: address of the head
 */
lineList *add_line_node(lineList **head, char *cmdline)
{
	lineList *new, *temp;

	new = malloc(sizeof(SepList));
	if (new == NULL)
		return (NULL);

	new->cmdline = cmdline;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
		*head = new;
	else
	{
		for (; temp->next != NULL; temp = temp->next)
			;
		temp->next = new;
	}

	return (*head);
}


/**
 * free_line_list - frees a lineList
 * @head: head of the linked list.
 *
 */
void free_line_list(lineList **head)
{
	lineList *temp, *current;

	if (head)
	{
		for (current = *head; current != NULL; current = temp)
		{
			temp = current->next;
			free(current);
		}
		*head = NULL;
	}
}


/**
 * add_node_list - add separators and command lines to the list
 * @headSep: head of separator list
 * @headList: head of command lines list
 * @input: input string
 *
 * Return: no return
 */
void add_node_list(SepList **headSep, lineList **headList, char *input)
{
	char *line;
	int i;

	input = swapChr(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node(headSep, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node(headSep, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");

	for (; line != NULL; line = _strtok(NULL, ";|&"))
	{
		line = swapChr(line, 1);
		add_line_node(headList, line);
	}
}

