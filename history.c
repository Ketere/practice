#include "shell.h"

/**
 * fetch_log_file - acquires the history file
 *
 * @data: structural parameter
 *
 * Return: string holding the allocated history file
 */

char *fetch_log_file(info_t *data)
{
	char *buffer, *directory;

	directory = _retrieve_env(data, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(ARCHIVE_NAME) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, ARCHIVE_NAME);
	return (buffer);
}

/**
 * jot_down_log - generates a file or appends to an existing file
 * @data: the structural parameter
 *
 * Return: 1 on success, otherwise -1
 */

int jot_down_log(info_t *data)
{
	ssize_t file_descriptor;
	char *filename = fetch_log_file(data);
	list_t *entry = NULL;

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descriptor == -1)
		return (-1);
	for (entry = data->history; entry; entry = entry->next)
	{
		_putsfd(entry->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(FLUSH_BUFFER, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * retrieve_log - reads history from file
 * @data: the structural parameter
 *
 * Return: record count on success, 0 otherwise
 */

int retrieve_log(info_t *data)
{
	int i, last = 0, line_counter = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat stats;
	char *buffer = NULL, *filename = fetch_log_file(data);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &stats))
		file_size = stats.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			compile_history_list(data, buffer + last, line_counter++);
			last = i + 1;
		}
	if (last != i)
		compile_history_list(data, buffer + last, line_counter++);
	free(buffer);
	data->record_count = line_counter;
	while (data->record_count-- >= RECORD_MAX)
		remove_node_at_index(&(data->history), 0);
	reset_history(data);
	return (data->record_count);
}

/**
 * compile_history_list - incorporates an entry into a historical linked list
 * @data: Structure storing potential arguments. Used for management
 * @buffer: buffer
 * @line_counter: the historical line counter, record count
 *
 * Return: Always 0
 */

int compile_history_list(info_t *data, char *buffer, int line_counter)
{
	list_t *entry = NULL;

	if (data->history)
		entry = data->history;
	append_node_end(&entry, buffer, line_counter);

	if (!data->history)
		data->history = entry;
	return (0);
}

/**
 * update_history - renumbers the history linked list after changes
 * @data: Structure storing potential arguments. Used for management
 *
 * Return: the new record count
 */

int update_history(info_t *data)
{
	list_t *entry = data->history;
	int i = 0;

	while (entry)
	{
		entry->num = i++;
		entry = entry->next;
	}
	return (data->record_count = i);
}
