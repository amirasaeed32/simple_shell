#include "shell.h"
/**
 * _eputs - prints an input string
 * @str: the string to be printed
 * Return: nothing
 */
void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}
/**
 * _eputchar - writes the character c to stderr
 * @c: the character to print
 * Return: on success 1,
 * on error, -1 is returned, and arrno is set appropriately
 */
int _eputchar(char c)
{
	static int a;
	static char b[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, b, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		b[a++] = c;
	return (1);
}
/**
 * _putfd - writes the character c to given fd
 * @c: the charaxter to print
 * @fd: the filedescriptor to write to
 * Return: on success 1.
 * on error, -1 is returned, and errno is set appropriately
 */
int _puftd(char c, int fd)
{
	static int a;
	static char b[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, b, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		b[a++] c;
	return (1);
}
/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
