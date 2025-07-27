/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:25 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 18:40:41 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*process_quoted_section(t_mini *mini, char *raw_arg, int *i,
		int len)
{
	char	quote_char;
	int		start;
	char	*tmp;
	char	*result;

	quote_char = raw_arg[*i];
	start = *i + 1;
	(*i)++;
	while (*i < len && raw_arg[*i] != quote_char)
		(*i)++;
	tmp = ft_substr(raw_arg, start, *i - start);
	if (!tmp)
		return (NULL);
	if (quote_char == '"')
	{
		result = expand_env_vars(mini, tmp);
		free(tmp);
	}
	else
		result = tmp;
	if (*i < len)
		(*i)++;
	return (result);
}

static char	*process_unquoted_section(t_mini *mini, char *raw_arg, int *i,
		int len)
{
	int		start;
	char	*tmp;
	char	*result;

	start = *i;
	while (*i < len && raw_arg[*i] != '"' && raw_arg[*i] != '\'')
		(*i)++;
	tmp = ft_substr(raw_arg, start, *i - start);
	if (!tmp)
		return (NULL);
	result = expand_env_vars(mini, tmp);
	free(tmp);
	return (result);
}

static char	*join_sections(char *result, char *section)
{
	char	*new_result;

	new_result = ft_strjoin(result, section);
	free(result);
	free(section);
	return (new_result);
}

char	*concatenate_sections(t_mini *mini, char *raw_arg, int len)
{
	char	*result;
	char	*section;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (raw_arg[i] == '"' || raw_arg[i] == '\'')
			section = process_quoted_section(mini, raw_arg, &i, len);
		else
			section = process_unquoted_section(mini, raw_arg, &i, len);
		if (!section)
		{
			free(result);
			return (NULL);
		}
		result = join_sections(result, section);
		if (!result)
			return (NULL);
	}
	return (result);
}
