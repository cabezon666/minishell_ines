/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:13:15 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/24 16:13:49 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_empty_string(void)
{
	char	*empty_str;

	empty_str = (char *)malloc(1);
	if (empty_str == NULL)
		return (NULL);
	empty_str[0] = '\0';
	return (empty_str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len1;
	size_t	start;
	size_t	end;
	size_t	trim_len;
	char	*trim_str;

	if (s1 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	start = 0;
	while (start < len1 && ft_strchr(set, s1[start]) != NULL)
		start++;
	end = len1;
	while (end > start && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	trim_len = end - start;
	if (trim_len == 0)
		return (create_empty_string());
	trim_str = (char *)malloc(trim_len + 1);
	if (trim_str == NULL)
		return (NULL);
	ft_strlcpy(trim_str, s1 + start, trim_len + 1);
	return (trim_str);
}
/*
int main(void)
{
	char *str1 = "XHello world!X";
	char *set1 = "X";
	char *result = ft_strtrim(str1, set1);
	if (result)
	{
		printf("Trimmed string: %s\n", result);
		free(result);
	}
	else
		printf("Memory allocation has failed");
	return (0);
}*/
