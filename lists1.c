#include "shell.h"

/**
 * calculate_list_length - determines length of linked list
 * @start_node: pointer to first node
 *
 * Return: size of list
 */


size_t calculate_list_length(const list_t *start_node)
{
	size_t length = 0;

	while (start_node)
	{
		start_node = start_node->next;
		length++;
	}
	return (length);
}

/**
 * convert_list_to_strings - returns an array of strings from the list->str
 * @first_node: pointer to first node
 *
 * Return: array of strings
 */


char **convert_list_to_strings(list_t *first_node)
{
	list_t *current_node = first_node;
	size_t count = calculate_list_length(first_node), j;
	char **str_array;
	char *string_data;

	if (!first_node || !count)
		return (NULL);
	str_array = malloc(sizeof(char *) * (count + 1));
	if (!str_array)
		return (NULL);
	for (count = 0; current_node; current_node = current_node->next, count++)
	{
		string_data = malloc(_strlen(current_node->str) + 1);
		if (!string_data)
		{
			for (j = 0; j < count; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		string_data = _strcpy(string_data, current_node->str);
		str_array[count] = string_data;
	}
	str_array[count] = NULL;
	return (str_array);
}


/**
 * display_list - prints all elements of a list_t linked list
 * @start_node: pointer to first node
 *
 * Return: size of list
 */


size_t display_list(const list_t *start_node)
{
	size_t list_size = 0;

	while (start_node)
	{
		_puts(convert_number(start_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(start_node->str ? start_node->str : "(nil)");
		_puts("\n");
		start_node = start_node->next;
		list_size++;
	}
	return (list_size);
}

/**
 * find_node_starts_with - returns node whose string starts with prefix
 * @starting_node: pointer to list head
 * @prefix_string: string to match
 * @next_char: the next character after prefix to match
 *
 * Return: match node or null
 */


list_t *find_node_starts_with(list_t *starting_node, char *prefix_string, char next_char)
{
	char *pointer_to_prefix = NULL;

	while (starting_node)
	{
		pointer_to_prefix = starts_with(starting_node->str, prefix_string);
		if (pointer_to_prefix && ((next_char == -1) || (*pointer_to_prefix == next_char)))
			return (starting_node);
		starting_node = starting_node->next;
	}
	return (NULL);
}

/**
 * retrieve_node_index - gets the index of a node
 * @head_node: pointer to list head
 * @searched_node: pointer to the node
 *
 * Return: index of node or -1
 */


ssize_t retrieve_node_index(list_t *head_node, list_t *searched_node)
{
	size_t node_index = 0;

	while (head_node)
	{
		if (head_node == searched_node)
			return (node_index);
		head_node = head_node->next;
		node_index++;
	}
	return (-1);
}
