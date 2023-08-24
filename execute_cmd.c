#include "main.h"
/**
 * execute_cmd - executes cmd lines
 * @shelldata: data structure
 *
 * Return: 1 (success)
 */
int execute_cmd(shell_state *shelldata)
{
	int state, exec;
	char *dir;
	pid_t pd;
	pid_t wpd;

	(void)wpd;
	exec = is_exec(shelldata);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = which_cmd(shelldata->arguments[0], shelldata->_environ);
		if (check_cmd_err(dir, shelldata) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = which_cmd(shelldata->arguments[0], shelldata->_environ);
		else
			dir = shelldata->arguments[0];
		execve(dir + exec, shelldata->arguments, shelldata->_environ);
	}
	else if (pd < 0)
	{
		perror(shelldata->argv[0]);
		return (1);
	}
	else
	{
		for (;;)
		{
			wpd = waitpid(pd, &state, WUNTRACED);
			if (WIFEXITED(state) || WIFSIGNALED(state))
				break;
		}
	}
	shelldata->status = state / 256;
	return (1);
}

/**
 * is_exec - determines if is an exec
 * @shelldata: data structure
 *
 * Return: 0 (not an executable), otherwise (it is)
 */
int is_exec(shell_state *shelldata)
{
	int i;
	char *input;
	struct stat st;

	input = shelldata->arguments[0];

	i = 0;
	while (input[i])
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
		i++;
	}

	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
		return (i);

	getError(shelldata, 127);
	return (-1);
}


/**
 * which_cmd - locates a cmd
 * @cmd: command name
 * @_environ: env var
 *
 * Return: location of the cmd
 */
char *which_cmd(char *cmd, char **_environ)
{
	int len_dir, len_cmd, i;
	char *path, *ptr_path, *token_path, *dir;
	struct stat st;

	path = get_env("PATH", _environ);

	if (path)
	{
		ptr_path = _strdup(path);
		token_path = _strtok(ptr_path, ":");
		len_cmd = _strlen(cmd);
		i = 0;
		while (token_path)
		{
			if (is_current(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			if (dir == NULL)
				return (NULL);
			_strcpy(dir, token_path), _strcat(dir, "/");
			_strcat(dir, cmd), _strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}


/**
 * is_current - checks if in the current dir
 * @path: path
 * @i: index
 *
 * Return: 1 (path is searchable), 0 otherwise
 */
int is_current(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
		*i += 1;

	if (path[*i])
		*i += 1;

	return (0);
}


/**
 * check_cmd_err - checks for user permissions
 * @dir: dest dir
 * @shelldata: data structure
 *
 * Return: 1 (error), 0 (no error)
 */
int check_cmd_err(char *dir, shell_state *shelldata)
{
	if (dir == NULL)
	{
		getError(shelldata, 127);
		return (1);
	}

	if (_strcmp(shelldata->arguments[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			getError(shelldata, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(shelldata->arguments[0], X_OK) == -1)
		{
			getError(shelldata, 126);
			return (1);
		}
	}

	return (0);
}
