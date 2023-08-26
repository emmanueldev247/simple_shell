#include "main.h"

/**
 * exit_cmd - exits the shell
 * @shelldata: data structure
 *
 * Return: 0 (success), failure otherwise
 */
int exit_cmd(shell_state *shelldata)
{
	unsigned int ustatus;
	int big_number, str_len, is_digit;

	if (shelldata->arguments[1])
	{
		is_digit = my_isdigit(shelldata->arguments[1]);
		ustatus = my_atoi(shelldata->arguments[1]);
		str_len = _strlen(shelldata->arguments[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (str_len > 10 || !is_digit || big_number)
		{
			get_error(shelldata, 2);
			shelldata->status = 2;
			return (1);
		}
		shelldata->status = (ustatus % 256);
	}
	return (0);
}
