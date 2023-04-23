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

/**
 * ev_print_func - returns the amount of identifiers.
 * @s: argument indentifier
 * @index: index of argument identifier.
 * Return: amount of identifiers.
 */

int ev_print_func(const char *s, int index)
{
	print_t pr[] = {
		{"c", print_chr}, {"s", print_str}, {"i", print_int},
		{"d", print_int}, {"b", print_bnr}, {"u", print_unt},
		{"o", print_oct}, {"x", print_hex}, {"X", print_upx},
		{"S", print_usr}, {"p", print_add}, {"li", prinlint},
		{"ld", prinlint}, {"lu", prinlunt}, {"lo", prinloct},
		{"lx", prinlhex}, {"lX", prinlupx}, {"hi", prinhint},
		{"hd", prinhint}, {"hu", prinhunt}, {"ho", prinhoct},
		{"hx", prinhhex}, {"hX", prinhupx}, {"#o", prinnoct},
		{"#x", prinnhex}, {"#X", prinnupx}, {"#i", print_int},
		{"#d", print_int}, {"#u", print_unt}, {"+i", prinpint},
		{"+d", prinpint}, {"+u", print_unt}, {"+o", print_oct},
		{"+x", print_hex}, {"+X", print_upx}, {" i", prinsint},
		{" d", prinsint}, {" u", print_unt}, {" o", print_oct},
		{" x", print_hex}, {" X", print_upx}, {"R", print_rot},
		{"r", print_rev}, {"%", print_prg}, {"l", print_prg},
		{"h", print_prg}, {" +i", prinpint}, {" +d", prinpint},
		{"+ i", prinpint}, {"+ d", prinpint}, {" %", print_prg},
		{NULL, NULL},
	};
	int i = 0, j = 0, first_index;

	first_index = index;
	while (pr[i].type_arg)
	{
		if (s[index] == pr[i].type_arg[j])
		{
			if (pr[i].type_arg[j + 1] != '\0')
				index++, j++;
			else
				break;
		}
		else
		{
			j = 0;
			i++;
			index = first_index;
		}
	}
	return (j);
}
