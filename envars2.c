#include "main.h"

/**
 * copyInfo - copy info
 * @env_name: name
 * @env_value: value
 *
 * Return: new env or alias
 */
char *copyInfo(char *env_name, char *env_value)
{
	int len_name, len_value, length;
	char *new_env;

	len_value = _strlen(env_value);
	len_name = _strlen(env_name);
	length = 2 + len_name + len_value;

	new_env = (char *)malloc(sizeof(char) * (length));
	if (new_env == NULL)
		return (NULL);

	_strcpy(new_env, env_name);
	_strcat(new_env, "=");
	_strcat(new_env, env_value);
	_strcat(new_env, "\0");

	return (new_env);
}

/**
 * setEnv - sets an env
 * @env_name: name of the env
 * @env_value: value of the env
 * @sd: data structure
 *
 */
void setEnv(char *env_name, char *env_value, shell_state *sd)
{
	char *var_env, *name_env;
	int i;

	i = 0;
	while (sd->_environ[i])
	{
		var_env = _strdup(sd->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, env_name) == 0)
		{
			free(sd->_environ[i]);
			sd->_environ[i] = copyInfo(name_env, env_value);
			free(var_env);
			return;
		}
		free(var_env);
		i++;
	}

	sd->_environ = _realloc_doublep(sd->_environ, i, sizeof(char *) * (i + 2));
	sd->_environ[i] = copyInfo(env_name, env_value);
	sd->_environ[i + 1] = NULL;
}

/**
 * cmp_setenv - compares env variables names
 * @shelldata: data structure
 *
 * Return: 1 (success)
 */
int cmp_setenv(shell_state *shelldata)
{
	if (shelldata->arguments[1] == NULL || shelldata->arguments[2] == NULL)
	{
		getError(shelldata, -1);
		return (1);
	}

	setEnv(shelldata->arguments[1], shelldata->arguments[2], shelldata);

	return (1);
}

/**
 * unset_env - deletes a environment variable
 * @shelldata: data structure
 *
 * Return: 1 on success.
 */
int unset_env(shell_state *shelldata)
{
	char *var_env, *name_env;
	char **realloc_environ;
	int i, j, k;

	if (shelldata->arguments[1] == NULL)
	{
		getError(shelldata, -1);
		return (1);
	}
	k = -1, i = 0;
	while (shelldata->_environ[i])
	{
		var_env = _strdup(shelldata->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, shelldata->arguments[1]) == 0)
			k = i;
		free(var_env);
		i++;
	}
	if (k == -1)
	{
		getError(shelldata, -1);
		return (1);
	}
	realloc_environ = (char **)malloc(sizeof(char *) * (i));
	i = j = 0;
	while (shelldata->_environ[i])
	{
		if (i != k)
		{
			realloc_environ[j] = shelldata->_environ[i];
			j++;
		}
		i++;
	}
	realloc_environ[j] = NULL;
	free(shelldata->_environ[k]);
	free(shelldata->_environ);
	shelldata->_environ = realloc_environ;
	return (1);
}
