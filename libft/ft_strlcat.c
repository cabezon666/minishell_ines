/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:26:41 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/21 16:26:42 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_length;
	size_t	src_length;
	size_t	i;

	src_length = ft_strlen(src);
	if (size == 0)
		return (src_length);
	dst_length = ft_strlen(dst);
	if (size <= dst_length)
		return (size + src_length);
	i = 0;
	while (src[i] && (dst_length + i) < (size - 1))
	{
		dst[dst_length + i] = src[i];
		i++;
	}
	dst[dst_length + i] = '\0';
	return (dst_length + src_length);
}
/*
int main(void)
{
	char dest[20] = "he";
	const char *source = "llo";
	size_t result;
	
	result = ft_strlcat(dest, source, sizeof(dest));
	printf("Resulting string: %s\n", dest);
	printf("Total length of string: %zu\n", result);
	return (0);
}*/
