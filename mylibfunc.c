#include "main.h"

/**
 * int_to_str - function to convert int to string.
 * @n: integer
 * Return: pointer to converted string
 */
char *int_to_str(int n)
{
	unsigned int num;
	int i, len = getLen(n);
	char *string;

	string = (char *)malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);

	string[len] = '\0';

	if (n < 0)
	{
		string[0] = '-';
		num = n * -1;
	}
	else
		num = n;

	for (i = len - 1; i >= 0; i--)
	{
		string[i] = (num % 10) + '0';
		num /= 10;
	}

	return (string);
}


/**
 * getLen - get the length of a number
 * @n: number
 *
 * Return: Length of the number
 */
int getLen(int n)
{
	long int len;
	unsigned int num;

	len = 0;
	if (n == 0)
		return (1);

	if (n < 0)
	{
		len++;
		num = n * -1;
	}
	else
		num = n;

	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

/**
 * my_atoi - Convert a string to an integer
 * @str: The string to convert
 *
 * Return: The converted integer
 */
int my_atoi(char *str)
{
int result, sign;

	result = 0;
	sign = 1;

	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\r' || *str == '\f' || *str == '\v')
		str++;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;

	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	return (sign * result);
}


/**
 * my_isdigit - checks if a string contains only digits
 * @s: the string to check
 *
 * Return: 1 if all characters are digits, 0 otherwise
 */
int my_isdigit(const char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}
