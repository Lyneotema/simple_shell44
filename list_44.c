#include "shell.h"
/**
 * list_len - Dictates the length of linked list
 * @h: Address of the first node
 * Return: The size of list.
 */
size_t list_len(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * list_to_strings - Return array of strings of list->str
 * @head: Address of the first node
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t m = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !m)
		return (NULL);
	strs = malloc(sizeof(char *) * (m + 1));
	if (!strs)
		return (NULL);
	for (m = 0; node; node = node->next, m++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < m; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[m] = str;
	}
	strs[m] = NULL;
	return (strs);
}


/**
 * print_list - It prints all elements of list_t linked list.
 * @h: Address of the first node.
 * Return: The size of list
 */
size_t print_list(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * node_starts_with - It returns a node with a string which starts with prefix
 * @node: Address of list head
 * @prefix: This is the string to match.
 * @c: Nxt. char after prefix to match
 * Return: Match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Finds index of the node.
 * @head: The address of list head.
 * @node: Address of the node
 * Return: The index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t m = 0;

	while (head)
	{
		if (head == node)
			return (m);
		head = head->next;
		m++;
	}
	return (-1);
}

