#include "main.h"

/**
 * _strdup - function to duplicate string
 * @str: string to be duplicated
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	char *duplicate;
	unsigned int len;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);
	duplicate = (char *)malloc(sizeof(char) * (len + 1));

	if (duplicate == NULL)
		return (NULL);

	duplicate = _memcpy(duplicate, str, len + 1);

	return (duplicate);
}


/**
 * _strlen - function that returns the length of a const char *
 * @s: pointer to string
 *
 * Return: the length of the string
 */
int _strlen(const char *s)
{
	int len;

	len = 0;
	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _strlenV2 - function that returns the length of a char *
 * @s: pointer to string
 *
 * Return: the length of the string
 */
int _strlenV2(char *s)
{
	int len;

	len = 0;
	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _memcpy - function that copies memory area
 * @dest: memory area to copy to
 * @src: memory area to copy from
 * @n: number of bytes to be filled
 *
 * Return: returns pointer to memory area dest
 */
char *_memcpy(void *dest, const void *src,  unsigned int n)
{
	unsigned int i;
	char *dest_cpy = (char *)dest;
	char *src_cpy = (char *)src;

	for (i = 0; i < n; i++)
		*(dest_cpy + i) = *(src_cpy + i);

	return (dest_cpy);
}

/**
 * _memcpyV2 - function that copies memory area (overload)
 * @dest: memory area to copy to
 * @src: memory area to copy from
 * @n: number of bytes to be filled
 *
 * Return: returns pointer to memory area dest
 */
char *_memcpyV2(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n; i++)
		*(dest + i) = *(src + i);

	return (dest);
}
