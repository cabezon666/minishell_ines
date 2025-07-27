/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:05:35 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:43:14 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(char **env, const char *var_name)
{
	int		i;
	size_t	len;

	if (!env || !var_name)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	update_existing_var(t_mini *mini, const char *var, char *new_entry)
{
	int	i;

	i = 0;
	while (mini->env[i] && ft_strncmp(mini->env[i], var, ft_strlen(var)) != 0)
		i++;
	if (mini->env[i])
	{
		free(mini->env[i]);
		mini->env[i] = new_entry;
		return (0);
	}
	return (1);
}

static char	**create_new_env(t_mini *mini, char *new_entry)
{
	char	**new_env;
	int		count;
	int		i;

	count = 0;
	while (mini->env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = mini->env[i];
		i++;
	}
	new_env[i++] = new_entry;
	new_env[i] = NULL;
	return (new_env);
}

int	update_env_var(t_mini *mini, const char *var, const char *value)
{
	char	**new_env;
	char	*new_entry;

	new_entry = ft_strjoin3(var, "=", value);
	if (!new_entry)
		return (1);
	if (update_existing_var(mini, var, new_entry) == 0)
		return (0);
	new_env = create_new_env(mini, new_entry);
	if (!new_env)
	{
		free(new_entry);
		return (1);
	}
	free(mini->env);
	mini->env = new_env;
	return (0);
}
