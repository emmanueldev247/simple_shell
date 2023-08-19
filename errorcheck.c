#include "main.h"

/**
 * check_error - function to check for error in input
 * @shelldata: data structure
 * @input: input string
 *
 * Return: 1 (error), otherwise (no error)
 */
int check_error(shell_state *shelldata, char *input)
{
	int begin, firstChar, errorPosition;

	begin = 0;
	firstChar = 0;
	errorPosition = 0;

	firstChar = first_non_whitespace(input, &begin);
	if (firstChar == -1)
	{
		/** here */
		return (1);
	}

}

/**
 * first_non_whitespace - function to find the first non whitespace character
 * @input: input string
 * @index: index of the found character
 *
 * Return: -1 (error), otherwise (no error)
 */
int first_non_whitespace(char *input, int *index)
{
	if (input == NULL || index == NULL)
		return (-1);

	int i = 0;

	while (input[i] != '\0')
	{
		if (input[i] == ';' || input[i] == '|' || input[i] == '&')
			return (-1);

		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else
		{
			*index = i;
			return (0);
		}
	}
	return (0);
}
