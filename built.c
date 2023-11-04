#include "shell.h"
/**
 * _myexit - exits the shell
 * @info: structure containing potential arguments. used to maintain
 * constant function prototype
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int ec;

	if (info->argv[1])
	{
		ec = _erratoi(info->argv[1]);
		if (ec == -1)
		{
			info->status = 2;
			print_error(info, "lllegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _mycd - changes the current directory of the process
 * @info: structure containing potential arguments. used to maintain
 * constant function prototype
 * Return: always 0
 */
int _mycd(info_t *info)
{
	char *s, *dr, b[1024];
	int ch;

	s = getcwd(b, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dr = _getenv(info, "HOME=");
		if (!dr)
			ch = chdir((dr = _getenv(info, "PWD=")) ? dr : "/");
		else
			ch = chdir(dr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ch = chdir((dr = _getenv(info, "OLDPWD=")) ? dr : "/");
	}
	else
		ch = chdir(info->argv[1]);
	if (ch == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(b, 1024));
	}
	return (0);
}
/**
 * _myhelp - changes the current directory of the process
 * @info: structure containing potential arguments. used to maintain
 * constant function prototype
 * Return: always 0
 */
int _myhelp(info_t *info)
{
	char **array;

	array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*array);
	return (0);
}
