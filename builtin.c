#include "main.h"

/**
 * executeCMD - finds builtin commands
 * @shelldata: data structure
 *
 * Return: 1 (success)
 */
int executeCMD(shell_state *shelldata)
{
	int (*cmd_builtins)(shell_state *shelldata);

	if (shelldata->arguments[0] == NULL)
		return (1);

	cmd_builtins = getBuiltin(shelldata->arguments[0]);

	if (cmd_builtins != NULL)
		return (cmd_builtins(shelldata));

	return (execute_cmd(shelldata));
	return (0);
}

/**
 * getBuiltin - function to pair the command in the arg
 * @cmd: command
 *
 * Return: function pointer of the builtin command
 */
int (*getBuiltin(char *cmd))(shell_state *)
{
	int i;
	builtin_list builtin_cmd[] = {
		{"cd", cd_cmd },
		{"env", env_cmd},
		{"setenv", cmp_setenv},
		{"unsetenv", unset_env},
		{"exit", exit_cmd},
	/*	{"help", help_cmd}; */
		{NULL, NULL }
	};

	i = 0;
	while (builtin_cmd[i].name)
	{
		if (_strcmp(builtin_cmd[i].name, cmd) == 0)
			break;
		i++;
	}

	return (builtin_cmd[i].func);
}
