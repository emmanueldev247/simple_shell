#include "main.h"

/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(shell_state *)
{
	builtin_t builtin[] = {
		{"cd", cd_cmd},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"help", help_cmd},
		{"exit", exit_cmd},
		{NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}


/**
 * get_error - calls the error according the builtin, syntax or permission
 * @shelldata: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(shell_state *shelldata, int eval)
{
char *error = NULL;

	if (eval == -1)
		error = error_env(shelldata);

	else if (eval == 127)
		error = error_not_found(shelldata);

	else if (eval == 126)
		error = error_path_126(shelldata);

	else if (eval == 2)
	{
		if (_strcmp("exit", shelldata->arguments[0]) == 0)
			error = error_exit_shell(shelldata);

		else if (_strcmp("cd", shelldata->arguments[0]) == 0)
			error = error_get_cd(shelldata);
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
 * exec_line - finds builtins and commands
 *
 * @datash: data relevant (arguments)
 * Return: 1 on success.
 */
int exec_line(shell_state *datash)
{
	int (*builtin)(shell_state *datash);

	if (datash->arguments[0] == NULL)
		return (1);

	builtin = get_builtin(datash->arguments[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
