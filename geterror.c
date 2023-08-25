#include "main.h"

/**
 * getError - calls the error function
 * @shelldata: data structure
 * @eval: error value
 *
 * Return: error output
 */
int getError(shell_state *shelldata, int eval)
{
	char *error = NULL;

	if (eval == -1)
		error = errorEnv(shelldata);

	else if (eval == 127)
		error = err_not_found(shelldata);

	else if (eval == 126)
		error = error_on_path126(shelldata);

	else if (eval == 2)
	{
		if (_strcmp("exit", shelldata->arguments[0]) == 0)
			error = err_exit(shelldata);

		else if (_strcmp("cd", shelldata->arguments[0]) == 0)
			error = error_cd(shelldata);
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		fflush(stdout);
		free(error);
	}

	shelldata->status = eval;
	return (eval);
}

/**
 * errorEnv - error message
 * @shelldata: data structure
 *
 * Return: error message.
 */
char *errorEnv(shell_state *shelldata)
{
	char *error;
	int length;
	char *msg;
	char *ver_str;

	msg = ": Unable to add/remove from environment\n";
	ver_str = int_to_str(shelldata->counter);
	length = _strlen(shelldata->argv[0]) + _strlen(ver_str);
	length += _strlen(shelldata->arguments[0]) + _strlen(msg) + 4;
	error = (char *)malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, shelldata->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shelldata->arguments[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * err_not_found - error message for cmd not found
 * @shelldata: data structure
 *
 * Return: error msg
 */
char *err_not_found(shell_state *shelldata)
{
	char *error;
	char *ver_str;
	int length;

	ver_str = int_to_str(shelldata->counter);
	length = _strlen(shelldata->argv[0]) + _strlen(ver_str);
	length += 16 + _strlen(shelldata->arguments[0]);

	error = (char *)malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, shelldata->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shelldata->arguments[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * error_on_path126 - error message for path failure
 * @shelldata: data structure
 *
 * Return: error msg
 */
char *error_on_path126(shell_state *shelldata)
{
	char *error;
	char *ver_str;
	int length;

	ver_str = int_to_str(shelldata->counter);
	length = _strlen(shelldata->argv[0]) + _strlen(ver_str);
	length += _strlen(shelldata->arguments[0]) + 24;

	error = (char *)malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, shelldata->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shelldata->arguments[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * err_exit - error message for exit
 * @sh: data structure
 *
 * Return: error msg
 */
char *err_exit(shell_state *sh)
{
	char *error;
	int length;
	char *ver_str;

	ver_str = int_to_str(sh->counter);
	length = _strlen(sh->argv[0]) + _strlen(ver_str);
	length += _strlen(sh->arguments[0]) + _strlen(sh->arguments[1]) + 23;
	error = (char *)malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, sh->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, sh->arguments[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, sh->arguments[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
