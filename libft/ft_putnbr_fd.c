/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:10:41 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/21 15:10:43 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c[20];
	int		ind;

	ind = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n == -2147483648)
		write(fd, "2147483648", 10);
	while (n > 0)
	{
		c[ind++] = (n % 10) + '0';
		n /= 10;
	}
	while (ind-- > 0)
		write(fd, &c[ind], 1);
}
/*
int main(void)
{
	int n = -54;
	ft_putnbr_fd(n, 1);
	return (0);
}*/
