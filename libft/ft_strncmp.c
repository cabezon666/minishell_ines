/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:06:40 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/22 15:06:41 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	if (n == 0)
		return (0);
	while (n > 0)
	{
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
		if (c1 == '\0' || c2 == '\0')
			return (c1 - c2);
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
/*
int main(void)
{
	char s1[] = "Everyone";
	char s2[] = "Everybody";
	int result = ft_strncmp(s1, s2, 6);
	printf("%d\n", result);
	return (0);
}*/
