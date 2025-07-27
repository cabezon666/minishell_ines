/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:54:47 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 15:00:13 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_special_var(char *str, int *i)
{
	char	*var_name;

	if (str[*i + 1] == '?')
	{
		var_name = ft_strdup("?");
		*i += 2;
		return (var_name);
	}
	return (NULL);
}

static char	*extract_regular_var(char *str, int *i)
{
	char	*var_name;
	int		j;

	j = 1;
	while (str[*i + j] && (ft_isalnum(str[*i + j]) || str[*i + j] == '_'))
		j++;
	var_name = ft_substr(str, *i + 1, j - 1);
	*i += j;
	return (var_name);
}

static char	*extract_var_name(char *str, int *i)
{
	char	*var_name;

	var_name = extract_special_var(str, i);
	if (var_name)
		return (var_name);
	return (extract_regular_var(str, i));
}

static char	*process_variable(t_mini *mini, char *str, int *i, char *result)
{
	char	*var_name;
	char	*var_value;
	char	*temp;

	var_name = extract_var_name(str, i);
	var_value = env_value(mini, var_name);
	temp = ft_strjoin(result, var_value);
	free(result);
	free(var_name);
	free(var_value);
	return (temp);
}

char	*expand_env_vars(t_mini *mini, char *str)
{
	char	*result;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'
				|| str[i + 1] == '_'))
		{
			result = process_variable(mini, str, &i, result);
		}
		else
		{
			result = ft_strjoin_char(result, str[i]);
			i++;
		}
	}
	return (result);
}
