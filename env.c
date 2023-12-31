#include "shell.h"
/**
 * _myenv - prints the current environment
 * @info: structrue containing potential arguments. used to maintain
 * constant function prototype
 * Return: always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - gets the value of an eviron variable
 * @info: structure containing potential arguments. used to maintain
 * @name: env var name
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - initialize a new environment variable,
 * or modify an existing one
 * @info: structure containing potential arguments. used to maintain
 * constant function prototype
 * Return: always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _myunsetenv - remove an environment variable
 * @info: structure containing potentail arguments. used to maintain
 * constant function prototype
 * Return: always 0
 */
int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);
	return (0);
}
/**
 * populate_env_list - populates env linked list
 * @info: structure containing potential arguments. used to maintain
 * constant function prototype
 * Return: always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; eviron[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}
