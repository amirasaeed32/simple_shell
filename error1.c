#include "shell.h"
/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int r = 0;

	if (*s == '+')
		s++;
	for (a = 0; s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			r *= 10;
			r += (s[a] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}
 /**
  * print_error - prints an error message
  * @info: the parameter & return info struct
  * @estr: string containing specified error type
  * Return: 0 if no numbers in string, converted number otherwise
  * -1 on error
  */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number if characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, c = 0;
	unsigned int _abs_, cu;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abs_ = input;
	cu = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + cu / a);
			c++;
		}
		cu %= a;
	}
	__putchar('0' + cu);
	c++;
	return (c);
}
/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char b[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" :
		"0123456789ABCDEF";
	ptr = &b[49];
	*ptr = '\0';
	do {
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: always 0
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ''))
		{
			buf[a] = '\0';
			break;
		}
}
