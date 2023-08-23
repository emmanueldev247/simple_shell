#include "main.h"

/**
 * add_svas_node - adds a variable at the end of a s_var list.
 * @head: head of the linked list.
 * @val: value of the variable.
 * @lvar: length of the variable.
 * @lval: length of the value.
 *
 * Return: address of the head.
 */
s_var *add_svar_node(s_var **head, char *val, int lvar, int lval)
{
	s_var *new, *temp;

	new = malloc(sizeof(s_var));
	if (new == NULL)
		return (NULL);

	new->varVal = val;
	new->valLen = lval;
	new->varLen = lvar;
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
 * free_svar_list - frees a s_var list
 * @head: head of the linked list.
 *
 * Return: no return.
 */
void free_svar_list(s_var **head)
{
	s_var *temp;
	s_var *curr;

	if (head)
	{
		for (curr = *head; curr != NULL; curr = temp)
		{
			temp = curr->next;
			free(curr);
		}
		*head = NULL;
	}
}
