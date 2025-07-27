/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:15:14 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/22 15:15:17 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big [i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (j < len - i && little[j] != '\0' && big[i + j] == little[j])
				j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	const char *big = "hello world";
	const char *little = "hello";
	char *result;
	
	result = ft_strnstr(big, little, 20);
	if (result)
	{
		printf("Found substring: %s\n", result);
	}
	else
	{
		printf("String not found.\n");
	}
	return (0);
}*/
