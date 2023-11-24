#include "shell.h"

/**
 * fill_memory - fills memory with a constant byte
 * @memory: the pointer to the memory area
 * @byte: the byte to fill *memory with
 * @bytes: the number of bytes to be filled
 * Return: (memory) a pointer to the memory area
 */

char *fill_memory(char *memory, char byte, unsigned int bytes)
{
	unsigned int i;

	for (i = 0; i < bytes; i++)
		memory[i] = byte;
	return (memory);
}

/**
 * free_strings - frees a string of strings
 * @string_array: string of strings to free
 */

void free_strings(char **string_array)
{
	char **arr = string_array;

	if (!string_array)
		return;
	while (*string_array)
		free(*string_array++);
	free(arr);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @ptr: pointer to previous allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */

void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
