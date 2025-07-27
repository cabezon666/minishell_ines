/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:23:37 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/22 11:23:39 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_char;

	last_char = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last_char = (char *)s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (last_char);
}
/*
int main(void)
{
	char const str[] = "hello";
	printf("%s\n", ft_strrchr(str, 'e'));
	return (0);
}*/
