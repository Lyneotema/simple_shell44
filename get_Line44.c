#include "shell.h"
/**
 * input_buf - chained Commands for Buffer.
 * @info: parameter struct.
 * @buf: The AddreSs to Buffer
 * @len: addreSS to len var.
 * Return: The Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t w = 0;
	size_t len_p = 0;

	if (!*len) /* if Nothing is Left in the Buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		w = getline(buf, &len_p, stdin);
#else
		w = _getline(info, buf, &len_p);
#endif
		if (w > 0)
		{
			if ((*buf)[w - 1] == '\n')
			{
				(*buf)[w - 1] = '\0'; /* Remove the Trailing newline */
				w--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = w;
				info->cmd_buf = buf;
			}
		}
	}
	return (w);
}

/**
 * get_input - Finds line minus(-) Newline
 * @info: The Parameter struct.
 *
 * Return: The Bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* The ';' command chain Buffer */
	static size_t i, j, len;
	ssize_t w = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	w = input_buf(info, &buf, &len);
	if (w == -1) /* EOF */
		return (-1);
	if (len) /* Then we Have commands Left in cHain buffer */
	{
		j = i; /* init New iterator to the Current buf position */
		p = buf + i; /* Get address fOr return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* Iterate to The ; or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increase pAst Nulled ';'' */
		if (i >= len) /* It has Hit End of buffer? */
		{
			i = len = 0; /* Reset Position and LenGth */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* It Passes back Pointer to the Current command Position */
		return (_strlen(p)); /* Return length Of current coMMand */
	}

	*buf_p = buf; /* else not CHAIN, Pass bAck Buffer from _getline() */
	return (w); /* return the length of Buffer from _getline() */
}

/**
 * read_buf - It reads Buffer
 * @info: The parameter struct.
 * @buf: BUFFER.
 * @i: SIZE.
 * Return: w
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t w = 0;

	if (*i)
		return (0);
	w = read(info->readfd, buf, READ_BUF_SIZE);
	if (w >= 0)
		*i = w;
	return (w);
}

/**
 * _getline - Finds next line of input from STDIN
 * @info: The parameter struct.
 * @ptr: Pointer to address of BUffer, PREallocated or NULL
 * @length: This is Size of the PREallocated ptr buffer if not NULL
 * Return: v
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t w = 0, v = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		v = *length;
	if (i == len)
		i = len = 0;

	w = read_buf(info, buf, &len);
	if (w == -1 || (w == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, v, v ? v + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (v)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	v += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = v;
	*ptr = p;
	return (v);
}

/**
 * sigintHandler - Blocks ctrl-C
 * @sig_num: Signal number.
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

