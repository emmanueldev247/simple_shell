#include "main.h"

/**
 * error_cd - error message for cd command
 * @shelldata: data structure
 *
 * Return: error msg
 */
char *error_cd(shell_state *shelldata)
{
	char *error, *ver_str, *msg;
	int length, len_id;

	ver_str = int_to_str(shelldata->counter);
	if (shelldata->arguments[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(shelldata->arguments[1]);
	}

	length = _strlen(shelldata->argv[0]) + _strlen(shelldata->arguments[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = (char *)malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	error = err_strcat(shelldata, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * err_strcat - function that concats error message
 * @shelldata: data structure
 * @msg: message
 * @error: output msg
 * @ver_str: counter lines
 *
 * Return: error message
 */
char *err_strcat(shell_state *shelldata, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, shelldata->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shelldata->arguments[0]);
	_strcat(error, msg);
	if (shelldata->arguments[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[1] = shelldata->arguments[1][1];
		illegal_flag[0] = '-';
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);

		free(illegal_flag);
	}
	else
	{
		_strcat(error, shelldata->arguments[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}
