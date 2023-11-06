#include "shell.h"
/**
 * get_history_file - gets the history file
 * @info: parameter struct
 * Return: allocated string containg history file
 */
char *get_history_file(info_t *info)
{
	char *b, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, dir);
	_strcat(b, "/");
	_strcat(b, HIST_FILE);
	return (b);
}
/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_history - reads history from file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *b = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	b = malloc(sizeof(char) * (fsize + 1));
	if (!b)
		return (0);
	rdlen = read(fd, b, fsize);
	b[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (b[a] == '\n')
		{
			b[a] = 0;
			build_history_list(info, b + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		buile_history_list(info, b + last, linecount++);
	free(b);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * buile_histry_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: always 0
 */
int build_history_list(info_t *info, char *b, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, b, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: structure containing potential arguments. used to maintain
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
