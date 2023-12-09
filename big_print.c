#include <unistd.h>
#include <stdarg.h>

/**
 * _putchar - writes the character c to stdout
 * @c: Character to print
 * Return: -1 on error, 1 on success
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

int str_print(const char *str)
{
	int count = 0;
	
	if (!str)
	{
		return (-1);
	}
	while (*str)
	{
		if (_putchar(*str) == -1)
		{
			return (-1);
		}
		str++;
		count++;
	}
	return (count);
}

int big_print(const char *format, ...)
{
	va_list args;
	int count = 0;
	const char *ptr = format;
	
	if (!format)
	{
		return (-1);
	}
	va_start(args, format);
	while (*ptr)
	{
		if (*ptr == '%' && *(ptr + 1))
		{
			switch (*(ptr + 1))
			{
				case 'c':
					count += _putchar(va_arg(args, int));
					break;
				case 's':
					count += str_print(va_arg(args, const char *));
					break;
				default:
					count += _putchar(*ptr);
					count += _putchar(*(ptr + 1));
					break;
			}
			ptr += 2;
		}
		else
		{
			count += _putchar(*ptr);
			ptr++;
		}
	}
	va_end(args);
	return(count);
}
