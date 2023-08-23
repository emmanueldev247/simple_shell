#include "main.h"

/**
 * check_error - function to check for error in input
 * @shelldata: data structure
 * @input: input string
 *
 * Return: -1 (error), otherwise (no error)
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
		print_error(shelldata, input, begin, 0);
		return (-1);
	}

	errorPosition = error_sep(input + begin, 0, *(input + begin));
	if (errorPosition != 0)
	{
		print_error(shelldata, input, begin + errorPosition, 1);
		return (-1);
	}

	return (0);
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
	int i;
	/* considered for testing */
	if (input == NULL || index == NULL)
		return (-1);

	i = 0;
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
/**
 * xRepeatedChar - counts the repetitions of a char
 * @input: input string
 * @i: index
 *
 * Return: repetitions
 */
int xRepeatedChar(char *input, int i)
{
	if (*(input - 1) == *input)
		return (xRepeatedChar(input - 1, i + 1));

	return (i);
}

/**
 * error_sep - finds syntax errors
 * @input: input string
 * @i: index
 * @last: last character read
 *
 * Return: index of error; 0 when there are no errors
 */
int error_sep(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ';')
		if (last == ';' || last == '&' || last == '|')
			return (i);

	if (*input == ' ' || *input == '\t')
		return (error_sep(input + 1, i + 1, last));

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = xRepeatedChar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = xRepeatedChar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep(input + 1, i + 1, *input));
}
