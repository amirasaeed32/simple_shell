#include "shell.h"
/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - checks if charater is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _isalpha - checks for alphabetic character
 * @c: the character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *s)
{
	int a, sign = 1, f = 0, output;
	unsigned int r = 0;

	for (a = 0; s[a] != '\0' && f != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;
		if (s[a] >= '0' && s[a] <= '9')
		{
			f = 1;
			r *= 10;
			r += (s[a] - '0');
		}
		else if (f == 1)
			f = 2;
	}
	if (sign == -1)
		output = -r;
	else
		output = r;
	return (output);
}
