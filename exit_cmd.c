#include "main.h"

/**
 * exit_shell - exits the shell
 *
 * @shelldata: data relevant (status and arguments)
 * Return: 0 on success.
 */
int exit_shell(shell_state *shelldata)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (shelldata->arguments[1] != NULL)
	{
		ustatus = my_atoi(shelldata->arguments[1]);
		is_digit = my_isdigit(shelldata->arguments[1]);
		str_len = _strlen(shelldata->arguments[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(shelldata, 2);
			shelldata->status = 2;
			return (1);
		}
		shelldata->status = (ustatus % 256);
	}
	return (0);
}

