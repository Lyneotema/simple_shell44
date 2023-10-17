#include "shell.h"
/**
 * is_chain - Check if current character in buffer is chain delimeter
 * @info: Parameter struct.
 * @buf: Char buffer.
 * @n: Pointer to the current position in the buf
 * Return: If chain delimeter 1, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *n)
{
	size_t j = *n;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found at the end of this command */
	{
		buf[j] = 0; /* replace ; with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*n = j;
	return (1);
}

/**
 * check_chain - Tests whether we should continue chaining based on last status
 * @info: Parameter struct
 * @buf: Character buffer
 * @n: Pointer to the current position in buf
 * @i: Commencing position in buf
 * @len: The length of buf
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *n, size_t i, size_t len)
{
	size_t j = *n;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*n = j;
}

/**
 * replace_alias - It replaces  aliases in tokenized string
 * @info: Parameter struct
 * Return: If replaced 1, otherwise 0
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *n;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		n = _strchr(node->str, '=');
		if (!n)
			return (0);
		n = _strdup(n + 1);
		if (!n)
			return (0);
		info->argv[0] = n;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - It replaces a string
 * @old: old string pointer
 * @new: The New string
 * Return: 1 If replaced, 0 Otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

