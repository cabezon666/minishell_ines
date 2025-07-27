/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:34:44 by lakkerma          #+#    #+#             */
/*   Updated: 2024/11/07 17:34:45 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += ft_putchar('-');
		if (n == -2147483648)
		{
			count += ft_putchar('2');
			n = 147483648;
		}
		else
			n = -n;
	}
	if (n == 0)
		return (count + ft_putchar('0'));
	if (n >= 10)
		count += ft_putnbr(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}

int	ft_putunbr(unsigned int u)
{
	int	count;

	count = 0;
	if (u == 0)
		return (count += ft_putchar('0'));
	if (u >= 10)
		count += ft_putnbr(u / 10);
	count += ft_putchar((u % 10) + '0');
	return (count);
}

int	ft_puthexnbr(unsigned long num, char case_type)
{
	int		count;
	char	*hex_digits;

	count = 0;
	if (case_type == 'x')
		hex_digits = "0123456789abcdef";
	else
		hex_digits = "0123456789ABCDEF";
	if (num == 0)
		return (count += ft_putchar('0'));
	if (num >= 16)
		count += ft_puthexnbr(num / 16, case_type);
	count += ft_putchar(hex_digits[num % 16]);
	return (count);
}

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	int				count;

	count = 0;
	if (!ptr)
	{
		count += ft_putstr("(nil)");
		return (count);
	}
	address = (unsigned long)ptr;
	count += ft_putstr("0x");
	if (address == 0)
		count += ft_putchar('0');
	else
		count += ft_puthexnbr(address, 'x');
	return (count);
}
