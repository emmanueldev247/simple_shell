#include "main.h"
/**
 * _strcat - function to concatenate two strings
 * @dest: destination string
 * @src: source string
 * Return: return a pointer to the resulting string in dest
 */
char *_strcat(char *dest, const char *src)
{
	int i, j;

	i = 0;
	while (dest[i] != '\0')
		i++;

	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcpy - function to clone strcpy()
 * @dest: destination
 * @src: source
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int len, i;

	len = _strlen(src);

	for (i = 0; i <= len; i++)
		dest[i] = src[i];

	dest[len + 1] = '\0';

	return (dest);
}
/**
 * _strcmp - Compare two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Return: -1 (s1 < s2), 0 (s1 == s2), 1 (s1 > s2)
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;

	if (s1[i] > s2[i])
		return (1);
	else if (s1[i] < s2[i])
		return (-1);
	else
		return (0);
}


/**
 * revString - Reverses a null-terminated string.
 * @s: The string to be reversed.
 *
 * Return: No return value.
 */
void revString(char *s)
{
	int length, start, end;
	char temp;

	if (s == NULL)
		return;

	length = 0;
	while (s[length] != '\0')
		length++;

	start = 0;
	end = length - 1;

	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;

		start++;
		end--;
	}
}
