/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:23:45 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/24 13:23:46 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
int main(void)
{
	char str[10] = "Hello";
	printf("Before ft_bzero: %s\n", str);
	ft_bzero(str, 4);
	printf("After ft_bzero: %s\n", str);
	int i = 0;
	while (i < 10)
	{
		printf("%02x ", (unsigned char)str[i]);
		i++;
	}
	return (0);
}*/
