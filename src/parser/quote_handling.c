/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:25 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:45:20 by inpastor         ###   ########.fr       */
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
		result = tmp;
	return (result);
}

char	*process_arg(t_mini *mini, char *raw_arg, int len)
{
	char	*arg;
	char	*tmp;
	char	quote_char;

	arg = ft_substr(raw_arg, 0, len);
	if (!arg)
		return (NULL);
	if ((arg[0] == '"' && arg[len - 1] == '"') || (arg[0] == '\''
			&& arg[len - 1] == '\''))
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
