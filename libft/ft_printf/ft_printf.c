/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:48:42 by lakkerma          #+#    #+#             */
/*   Updated: 2024/11/04 14:55:44 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s != '\0')
	{
		count += ft_putchar(*s);
		s++;
	}
	return (count);
}

static int	handle_format(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (specifier == 'p')
		count += ft_putptr(va_arg(args, void *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (specifier == 'u')
		count += ft_putunbr(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		count += ft_puthexnbr(va_arg(args, unsigned int), specifier);
	else if (specifier == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		i;
	va_list	args;

	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			format++;
			count += handle_format(format[i], args);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
	char c = 'A';
	char *str = "Hello world";
	int num = 42;
	int nbr = 652;
	unsigned int u_num = 3000000000;
	void *ptr = (void *)0x12345678;
	ft_printf("Character: %c\n", c);
	printf("Printf Character: %c\n", c);

	ft_printf("String: %s\n", str);
	printf("Printf String: %s\n", str);

	ft_printf("Integer: %d\n", num);
	printf("Printf Integer: %d\n", num);

	ft_printf("Decimal: %i\n", nbr);
	printf("Printf Decimal: %i\n", nbr);

	ft_printf("Unsigned integer: %u\n", u_num);
	printf("Printf Unsigned interger: %u\n", u_num);

	ft_printf("Pointer: %p\n", ptr);
	printf("Printf Pointer: %p\n", ptr);

	ft_printf("Hexadecimal uppercase: %X\n", num);
	printf("Printf Hexadecimal uppercase: %X\n", num);

	ft_printf("Hexadecimal lowercase: %x\n", num);
	printf("Printf Hexadecimal lowercase: %x\n", num);

	ft_printf("Percentage: %%\n");
	printf("Printf Percentage: %%\n");
	return (0);
}*/
