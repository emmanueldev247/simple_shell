#include "main.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeated_char(input, 0);
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
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
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
 * print_syntax_error - prints when a syntax error is found
 *
 * @shelldata: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_error(shell_state *shelldata, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = int_to_str(shelldata->counter);
	length = _strlen(shelldata->argv[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, shelldata->argv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}
/**
 * check_error - function to check for error in input
 * @shelldata: data structure
 * @input: input string
 *
 * Return: -1 (error), otherwise (no error)
 */
int check_error(shell_state *shelldata, char *input)
{
	int begin, firstChar, i;

	i = 0;
	begin = 0;
	firstChar = 0;

	firstChar = first_non_whitespace(input, &begin);
	if (firstChar == -1)
	{
		print_syntax_error(shelldata, input, begin, 0);
		return (-1);
	}

	i = error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_error(shelldata, input, begin + i, 1);
		return (-1);
	}
	return (0);
}
