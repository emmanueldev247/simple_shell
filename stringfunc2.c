#include "main.h"
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
	{
		dest[i] = src[i];
	}

	dest[len + 1] = '\0';

	return (dest);
}

/**
 * _strcat - function to concatenate two strings
 * @dest: destination string
 * @src: source string
 * Return: return a pointer to the resulting string in dest
 */
char *_strcat(char *dest, const char *src)
{
	int src_len, dest_len;

	dest_len = _strlen(dest);
	src_len = 0;

	while (src[src_len] != '\0')
	{
		dest[dest_len] = src[src_len];
		dest_len++;
		src_len++;
	}

	dest[dest_len + 1] = '\0';

	return (dest);
}
