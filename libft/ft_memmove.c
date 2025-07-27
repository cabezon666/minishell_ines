/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:09:02 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/24 10:09:03 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (d < s || d >= s + n)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	return (dest);
}
/*
int main(void)
{
	char str1[20] = "goodbye";
	char str2[20] = "hello world";
	
	printf("Before overlapping:\n");
	printf("Before ft_memmove: %s\n", str1);
	ft_memmove(str1 + 2, str1, 5);
	printf("After ft_memmove: %s\n", str1);
	
	printf("Before overlapping:\n");
	printf("Before ft_memmove: %s\n", str2);
	ft_memmove(str2, str2 + 6, 5);
	printf("After ft_memmove: %s\n", str2);
	return (0);
}*/
