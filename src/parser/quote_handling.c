/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:25 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 18:42:14 by ewiese-m         ###   ########.fr       */
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

static int	count_quotes(char *raw_arg, int len)
{
	int	has_quotes;
	int	i;

	has_quotes = 0;
	i = 0;
	while (i < len)
	{
		if (raw_arg[i] == '"' || raw_arg[i] == '\'')
			has_quotes++;
		i++;
	}
	return (has_quotes);
}

static char	*process_simple_arg(t_mini *mini, char *arg, int len)
{
	char	*tmp;
	char	quote_char;

	if (len >= 2 && ((arg[0] == '"' && arg[len - 1] == '"') || (arg[0] == '\''
				&& arg[len - 1] == '\'')))
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

char	*process_arg(t_mini *mini, char *raw_arg, int len)
{
	char	*arg;
	int		has_quotes;

	has_quotes = count_quotes(raw_arg, len);
	if (has_quotes > 2 || (has_quotes > 0 && (raw_arg[0] != '"'
				&& raw_arg[0] != '\'')))
		return (concatenate_sections(mini, raw_arg, len));
	arg = ft_substr(raw_arg, 0, len);
	if (!arg)
		return (NULL);
	return (process_simple_arg(mini, arg, len));
}
