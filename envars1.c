#include "main.h"

/**
 * cmp_env - compares env var names
 * @nenv: name of the environment variable
 * @name: name to check against
 *
 * Return: 0 (not equal); otherwise (equal)
 */
int cmp_env(const char *nenv, const char *name)
{
	int i;

	i = 0;
	while (nenv[i] != '=' && nenv[i] == name[i])
		i++;

	if (nenv[i] == '=')
		return (i + 1);
	else
		return (0);
}


/**
 * get_env - get an env var
 * @var_name: name of env var
 * @_env: environment variable
 *
 * Return: value of the environment variable; otherwise NULL
 */
char *get_env(const char *var_name, char **_env)
{
	int i, mov;
	char *ptr_env;

	mov = 0;
	ptr_env = NULL;

	i = 0;
	while (_env[i])
	{
		mov = cmp_env(_env[i], var_name);
		if (mov)
		{
			ptr_env = _env[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(shell_state *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
