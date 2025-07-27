/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:19:04 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/24 11:19:05 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		find_c;
	size_t				i;

	str = (const unsigned char *)s;
	find_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == find_c)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	const char str[] = "hello";
	char *result;
	result = ft_memchr(str, 'l', 6);
	printf("%s\n", result);
	return (0);
}*/
