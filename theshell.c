#include "main.h"

/**
 * theshell - loop of the shell
 * @shelldata: data structure containing shell data
 *
 * Return: nothing
 */
void theshell(shell_state *shelldata)
{
	int allow;
	char *input = NULL;
	size_t len = 0;
	ssize_t read;

	allow = 1;
	while (allow)
	{
		write(STDOUT_FILENO, "-> ", 3);
		fflush(stdout);

		read = getline(&input, &len, stdin);
		if (read != -1)
		{
			input = remove_comment(input);
			if (input == NULL)
				continue;
			/*here*/

