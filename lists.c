#include "shell.h"

/**
 * append_first_node - adds a node to the start of the list
 * @main_node: address of pointer to head node
 * @string_data: str field of node
 * @node_index: node index used by history
 *
 * Return: size of list
 */


list_t *append_first_node(list_t **main_node, const char *string_data, int node_index)
{
	list_t *new_main_node;

	if (!main_node)
		return (NULL);
	new_main_node = malloc(sizeof(list_t));
	if (!new_main_node)
		return (NULL);
	_memset((void *)new_main_node, 0, sizeof(list_t));
	new_main_node->num = node_index;
	if (string_data)
	{
		new_main_node->str = _strdup(string_data);
		if (!new_main_node->str)
		{
			free(new_main_node);
			return (NULL);
		}
	}
	new_main_node->next = *main_node;
	*main_node = new_main_node;
	return (new_main_node);
}

/**
 * append_last_node - adds a node to the end of the list
 * @main_node: address of pointer to head node
 * @string_data: str field of node
 * @node_index: node index used by history
 *
 * Return: size of list
 */


list_t *append_last_node(list_t **main_node, const char *string_data, int node_index)
{
	list_t *new_item, *current_node;

	if (!main_node)
		return (NULL);

	current_node = *main_node;
	new_item = malloc(sizeof(list_t));
	if (!new_item)
		return (NULL);
	_memset((void *)new_item, 0, sizeof(list_t));
	new_item->num = node_index;
	if (string_data)
	{
		new_item->str = _strdup(string_data);
		if (!new_item->str)
		{
			free(new_item);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_item;
	}
	else
		*main_node = new_item;
	return (new_item);
}

/**
 * print_list_string - prints only the str element of a list_t linked list
 * @node_ptr: pointer to first node
 *
 * Return: size of list
 */


size_t print_list_string(const list_t *node_ptr)
{
	size_t counter = 0;

	while (node_ptr)
	{
		_puts(node_ptr->str ? node_ptr->str : "(nil)");
		_puts("\n");
		node_ptr = node_ptr->next;
		counter++;
	}
	return (counter);
}

/**
 * remove_node_at_index - deletes node at given index
 * @main_node: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */


int remove_node_at_index(list_t **main_node, unsigned int index)
{
	list_t *current_node, *previous_node;
	unsigned int i = 0;

	if (!main_node || !*main_node)
		return (0);

	if (!index)
	{
		current_node = *main_node;
		*main_node = (*main_node)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *main_node;
	while (current_node)
	{
		if (i == index)
		{
			previous_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		i++;
		previous_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}

/**
 * clear_list - frees all nodes of a list
 * @pointer_to_head: address of pointer to head node
 *
 * Return: void
 */


void clear_list(list_t **pointer_to_head)
{
	list_t *current_node, *next_node, *main_head;

	if (!pointer_to_head || !*pointer_to_head)
		return;
	main_head = *pointer_to_head;
	current_node = main_head;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	*pointer_to_head = NULL;
}
