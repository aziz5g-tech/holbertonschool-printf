#include "main.h"

/**
 * flush_buffer - writes buffer content to stdout and resets buffer
 * @buffer: the buffer to flush
 * @index: pointer to buffer index
 *
 * Return: number of characters written
 */
int flush_buffer(char *buffer, int *index)
{
	int written = 0;

	if (*index > 0)
	{
		written = write(1, buffer, *index);
		*index = 0;
	}

	return (written);
}

/**
 * add_to_buffer - adds a character to buffer
 * @c: character to add
 * @buffer: the buffer to add to
 * @index: pointer to buffer index
 *
 * Return: 1 on success
 */
int add_to_buffer(char c, char *buffer, int *index)
{
	if (*index >= BUFFER_SIZE)
	{
		flush_buffer(buffer, index);
	}

	buffer[(*index)++] = c;

	return (1);
}
