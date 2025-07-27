/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:08:12 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/24 15:08:12 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate_string(size_t size)
{
	char	*str;

	str = (char *)malloc(size);
	if (str != NULL)
		str[0] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	substr_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (allocate_string(1));
	if (len < s_len - start)
		substr_len = len;
	else
		substr_len = s_len - start;
	substr = allocate_string((substr_len + 1) * sizeof (char));
	if (substr == NULL)
		return (NULL);
	ft_memcpy(substr, s + start, substr_len);
	substr[substr_len] = '\0';
	return (substr);
}
/*
int main(void)
{
	char *str = "Hello, world!";
	char *substr;

	substr = ft_substr(str, 0, 4);
	printf("Test: %s\n", substr);
	free(substr);
	return (0);
}*/
