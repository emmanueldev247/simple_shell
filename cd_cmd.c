#include "main.h"

/**
 * cd_cmd - changes directory
 * @shelldata: data structure
 *
 * Return: 1 (success)
 */
int cd_cmd(shell_state *shelldata)
{
	char *target_dir;
	int is_home, is_home_symbol, is_ddash;

	target_dir = shelldata->arguments[1];

	if (target_dir != NULL)
	{
		is_ddash = _strcmp("--", target_dir);
		is_home_symbol = _strcmp("~", target_dir);
		is_home = _strcmp("$HOME", target_dir);
	}

	if (target_dir == NULL || !is_ddash || !is_home_symbol || !is_home)
	{
		cd_home(shelldata);
		return (1);
	}

	if (_strcmp(".", target_dir) == 0 || _strcmp("..", target_dir) == 0)
	{
		cd_to_dot(shelldata);
		return (1);
	}

	if (_strcmp("-", target_dir) == 0)
	{
		cd_to_previous(shelldata);
		return (1);
	}

	cd_here(shelldata);

	return (1);
}

/**
 * cd_to_dot - cd to parent directory
 * @shelldata: data structure
 *
 */
void cd_to_dot(shell_state *shelldata)
{
	char *dir, *cp_pwd, *cp_strtok_pwd;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, shelldata);
	dir = shelldata->arguments[1];
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, shelldata);
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	revString(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			revString(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, shelldata);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", shelldata);
	}
	shelldata->status = 0;
	free(cp_pwd);
}

/**
 * cd_here - changes to a input directory
 * @shelldata: data structure
 */
void cd_here(shell_state *shelldata)
{
	char *dir, *cp_pwd, *cp_dir;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));

	dir = shelldata->arguments[1];
	if (chdir(dir) == -1)
	{
		get_error(shelldata, 2);
		return;
	}

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, shelldata);

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, shelldata);

	free(cp_dir);
	free(cp_pwd);

	shelldata->status = 0;

	chdir(dir);
}

/**
 * cd_to_previous - changes to prev dir
 * @shelldata: data structure
 */
void cd_to_previous(shell_state *shelldata)
{
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", shelldata->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, shelldata);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, shelldata);
	else
		set_env("PWD", cp_oldpwd, shelldata);

	p_pwd = _getenv("PWD", shelldata->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);
	fflush(stdout);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	shelldata->status = 0;

	chdir(p_pwd);
}

/**
 * cd_home - changes to home directory
 *
 * @shelldata: data relevant (environ)
 * Return: no return
 */
void cd_home(shell_state *shelldata)
{
	char pwd[PATH_MAX];
	char *p_pwd, *home;

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", shelldata->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, shelldata);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(shelldata, 2);
		free(p_pwd);
		return;
	}

	set_env("PWD", home, shelldata);
	set_env("OLDPWD", p_pwd, shelldata);
	free(p_pwd);
		shelldata->status = 0;
}
