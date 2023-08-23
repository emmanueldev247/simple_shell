#include "main.h"

/**
 * _strtok - customized implementation of strtok function
 *			to split a string by some delimiter
 * @input: string to split
 * @delimiter: delimiter
 *
 * Return: string in split form
 */
char *_strtok(char *input, const char *delimiter)
{
	unsigned int i, flag;
	char *str_start;
	static char *split, *str_end;

	if (input != NULL)
	{
		if (compare_str(input, delimiter))
			return (NULL);

		split = input;
		i = _strlen(input);
		str_end = input + i;
	}
	str_start = split;
	if (str_start == str_end)
		return (NULL);

	for (flag = 0; *split; split++)
	{
		if (split != str_start)
			if (*split && *(split - 1) == '\0')
				break;
		i = 0;
		while (delimiter[i])
		{
			if (*split == delimiter[i])
			{
				*split = '\0';
				if (split == str_start)
					str_start++;
				break;
			}
			i++;
		}
		if (flag == 0 && *split)
			flag = 1;
	}
	if (flag == 0)
		return (NULL);
	return (str_start);
}

/**
 * compare_str - compare characters of strings
 * @input: input string
 * @delimeter: delimiter
 *
 * Return: 1 (equal); 0 otherwise
 */
int compare_str(char *input, const char *delimeter)
{
	int found;
	const char *d;

	while (*input)
	{
		found = 0;
		for (d = delimeter; *d; d++)
		{
			if (*input == *d)
			{
				found = 1;
				break;
			}
		}
		if (!found)
			return (0);
		input++;
	}
	return (1);
}