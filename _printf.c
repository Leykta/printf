#include "main.h"

/**
 * _printf - formatted output conversion and print data.
 * @format: input string.
 *
 * Return: number of chars that are printed.
 */

int _printf(const char *format, ...)
{
	unsigned int tmp = 0, len = 0, ibuf = 0;
	va_list arguments;
	int (*function)(va_list, char *, unsigned int);
	char *buffer;

	va_start(arguments, format), buffer = malloc(sizeof(char) * 1024);
	if (!format || !buffer || (format[tmp] == '%' && !format[tmp + 1]))
		return (-1);
	if (!format[tmp])
		return (0);
	for (tmp = 0; format && format[tmp]; tmp++)
	{
		if (format[tmp] == '%')
		{
			if (format[tmp + 1] == '\0')
			{	
				print(buffer, ibuf), free(buffer), va_end(arguments);
				return (-1);
			}
			else
			{	
				function = get_print_func(format, tmp + 1);
				if (function == NULL)
				{
					if (format[tmp + 1] == ' ' && !format[tmp + 2])
						return (-1);
					handle(buffer, format[tmp], ibuf), len++, tmp--;
				}
				else
				{
					len += function(arguments, buffer, ibuf);
					tmp += ev_print_func(format, tmp + 1);
				}
			} tmp++;
		}
		else
			handle(buffer, format[tmp], ibuf), len++;
		for (ibuf = len; ibuf > 1024; ibuf -= 1024)
			;
	}
	print(buffer, ibuf), free(buffer), va_end(arguments);
	return (len);
}

/**
 * print_buf - prints buffer
 * @buf: buffer pointer
 * @nbuf: number of bytes to print
 * Return: number of bytes printed.
 */

int print(char *buf, unsigned int nbuf)
{
	return (write(1, buf, nbuf));
}

/**
 * handl_buf - concatenates the buffer characters
 * @buf: buffer pointer
 * @c: charcter to concatenate
 * @ibuf: index of buffer pointer
 * Return: index of buffer pointer.
 */

unsigned int handle(char *buf, char c, unsigned int ibuf)
{
	if (ibuf == 1024)
	{
		print_buf(buf, ibuf);
		ibuf = 0;
	}
	buf[ibuf] = c;
	ibuf++;
	return (ibuf);
}
