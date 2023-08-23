#include "main.h"

/**
 * construct_err - Constructs an error message
 * @shdata: data structure
 * @i: counter component of the error message
 * @m1: error message component
 * @m2: second part of the error message
 * @m3: third part of the error message
 *
 * Return: Pointer to the allocated error message or NULL if allocation fails
 */
char *construct_err(shell_state *shdata, char *i, char *m1, char *m2, char *m3)
{
	char *error_message;
	int length;

	length = _strlen(shdata->argv[0]) + _strlen(i);
	length += _strlen(m1) + _strlen(m2) + _strlen(m3) + 2;

	error_message = (char *)malloc(sizeof(char) * (length + 1));
	if (error_message != NULL)
	{
		_strcpy(error_message, shdata->argv[0]);
		_strcat(error_message, ": ");
		_strcat(error_message, i);
		_strcat(error_message, m2);
		_strcat(error_message, m1);
		_strcat(error_message, m3);
		_strcat(error_message, "\0");
	}
	else
	{
		free(i);
		return (NULL);
	}

	return (error_message);
}

/**
 * print_error_message - prints an error message to stderr
 * @error_message: error message to print
 *
 * Return: nothing
 */
void print_error_message(char *error_message)
{
	if (error_message != NULL)
	{
		write(STDERR_FILENO, error_message, _strlen(error_message));
		free(error_message);
	}
}

/**
 * determine_error_message - determines the message
 *						based on the input character
 * @input: input string
 * @i: current position in the input string
 * @bool: flag
 *
 * Return: The determined message
 */
char *determine_error_message(char *input, int i, int bool)
{
	char *message;

	if (input[i] == ';')
	{
		if (bool == 0)
		{
			if (input[i + 1] == ';')
				message = ";;";
			else
				message = ";";
		}
		else
		{
			if (input[i - 1] == ';')
				message = ";;";
			else
				message = ";";
		}
	}
	else if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			message = "||";
		else
			message = "|";
	}
	else if (input[i] == '&')
	{
		if (input[i + 1] == '&')
			message = "&&";
		else
			message = "&";
	}

	return (message);
}

/**
 * print_error - displays error message
 * @shelldata: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 *
 * Return: no return
 */
void print_error(shell_state *shelldata, char *input, int i, int bool)
{
	char *message, *msg2, *msg3, *error_message, *counter;

	message = determine_error_message(input, i, bool);

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = int_to_str(shelldata->counter);

	error_message = construct_err(shelldata, counter, message, msg2, msg3);

	print_error_message(error_message);

	free(counter);
}
