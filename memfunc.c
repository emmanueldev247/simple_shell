#include "main.h"
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
 * _realloc - reallocates a memory block of a pointer
 * @ptr: double pointer to the memory previously allocated
 * @old_size: size, in bytes, of the allocated space of ptr
 * @new_size: new size, in bytes, of the new memory block
 *
 * Return: ptr
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL
 */
char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size)
{
	char *newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}


/**
 * _reallocdoublep - reallocates memory for a double pointer
 * @ptr: old double pointer
 * @size: size of old pointer
 * @new_size: new size of new pointer
 *
 * Return: new pointer
 */
char **_reallocdoublep(char **ptr, unsigned int size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	if (size <= new_size)
	{
		for (i = 0; i < size; i++)
			newptr[i] = ptr[i];
	}
	else
	{
		for (i = 0; i < new_size; i++)
			newptr[i] = ptr[i];
	}

	free(ptr);

	return (newptr);
}
