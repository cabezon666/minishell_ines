/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:43:15 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/24 14:43:16 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	length;
	size_t	i;
	char	*dup;

	i = 0;
	length = 0;
	while (s[length] != '\0')
		length++;
	dup = (char *)malloc((length + 1) * sizeof (char));
	if (dup == NULL)
		return (NULL);
	while (i < length)
	{
		dup[i] = s[i];
		i++;
	}
	dup[length] = '\0';
	return (dup);
}
/*
int main (void)
{
	const char *str = "hello";
	char *dup = ft_strdup(str);
	
	if (dup == NULL)
		printf("Function returned NULL of input: %s\n", str);
	else
	{
		printf("Original: %s\n", str);
		printf("Duplicate: %s\n", dup);
		free(dup);
	}
	return (0);
}*/
