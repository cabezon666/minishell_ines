/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:25 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 17:45:14 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_quoted_arg(t_mini *mini, char *arg, char quote_char)
{
	char	*tmp;
	char	*result;

	tmp = ft_substr(arg, 1, ft_strlen(arg) - 2);
	free(arg);
	if (!tmp)
		return (NULL);
	if (quote_char == '"')
	{
		result = expand_env_vars(mini, tmp);
		free(tmp);
	}
	else
	{
		result = tmp;
	}
	return (result);
}

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
		result = expand_env_vars(mini, tmp);
	else
		result = ft_strdup(tmp);
	free(tmp);
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

static char	*concatenate_sections(t_mini *mini, char *raw_arg, int len)
{
	char	*result;
	char	*section;
	char	*new_result;
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
		new_result = ft_strjoin(result, section);
		free(result);
		free(section);
		result = new_result;
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*process_arg(t_mini *mini, char *raw_arg, int len)
{
	char *arg;
	char *tmp;
	char quote_char;

	int has_quotes = 0;
	int i = 0;
	while (i < len)
	{
		if (raw_arg[i] == '"' || raw_arg[i] == '\'')
			has_quotes++;
		i++;
	}

	if (has_quotes > 2 || (has_quotes > 0 && (raw_arg[0] != '"'
				&& raw_arg[0] != '\'')))
		return (concatenate_sections(mini, raw_arg, len));

	arg = ft_substr(raw_arg, 0, len);
	if (!arg)
		return (NULL);
	if ((arg[0] == '"' && arg[len - 1] == '"') || (arg[0] == '\'' && arg[len
			- 1] == '\''))
	{
		quote_char = arg[0];
		arg = handle_quoted_arg(mini, arg, quote_char);
	}
	else
	{
		tmp = expand_env_vars(mini, arg);
		free(arg);
		arg = tmp;
	}
	return (arg);
}