/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:18:35 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/24 16:18:36 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_length(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_fill_str(char *str, int size, int nbr, int n)
{
	while (size > nbr)
	{
		str[size - 1] = (n % 10) + '0';
		n /= 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		nbr;

	nbr = 0;
	len = ft_get_length(n);
	str = (char *)malloc(sizeof (char) * len + 1);
	if (!str)
		return (0);
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = 147483648;
		nbr = 2;
	}
	if (n < 0)
	{
		str[0] = '-';
		nbr = 1;
		n = -n;
	}
	ft_fill_str(str, len, nbr, n);
	str[len] = '\0';
	return (str);
}
/*
int main(void)
{
	int num = -42;
	char *result = ft_itoa(num);
	if (result)
	{
		printf("String representation of %d: '%s'\n", num, result);
		free(result);
	}
	else
		printf("Memory allocation failed");
	return (0);
}*/
