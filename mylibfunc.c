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
	int len;
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

