#include "shell.h"
/**
 * get_environ - returns tthe string array copy of environ
 * @info: structure containing potential arguments. used to maintain
 * constant function prototype
 * Return: always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}
/**
 * _unsetenv - remove an environment variable
 * @info: structurd containing potential arguments. used to maintain
 * constant function prototype
 * Return: 1 on delete, 0 otherwise
 * @var: the string env variable property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}
/**
 * _setenv - initialize a new environment variable
 * or modify an existing one
 * @info: structure containig potential arguments. used to maintain
 * constant function prototype
 * @var: the string env var property
 * @value: the string env var value
 * Return: aalways 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *b = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	b = malloc(_strlen(var) + _strlen(value) + 2);
	if (!b)
		return (1);
	_strcpy(b, var);
	_strcat(b, "=");
	_strcat(b, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = b;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), b, 0);
	free(b);
	info->env_changed = 1;
	return (0);
}
