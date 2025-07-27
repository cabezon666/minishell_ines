/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:16:10 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/24 16:16:11 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_next_word(char const *s, size_t start, size_t finish)
{
	char	*words;
	size_t	len;

	len = finish - start;
	words = (char *)malloc((len + 1) * sizeof (char));
	if (!words)
		return (NULL);
	ft_memcpy(words, s + start, len);
	words[len] = '\0';
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	start;
	size_t	finish;
	size_t	words;
	size_t	i;

	words = ft_count(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	while (i < words)
	{
		while (s[start] && s[start] == c)
			start++;
		finish = start;
		while (s[finish] && s[finish] != c)
			finish++;
		result[i] = get_next_word(s, start, finish);
		start = finish;
		i++;
	}
	result[i] = NULL;
	return (result);
}
/*
int main(void)
{
	char *str = "this is a test";
	int i = 0;
	char **result = ft_split(str, ' ');
	while (result[i] != NULL)
	{
		printf("result[%d]: %s\n", i, result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}*/
