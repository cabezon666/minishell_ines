/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:25:31 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:43:36 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_env_var(char **env, const char *name)
{
	size_t	len;
	int		i;

	i = 0;
	if (!env || !name)
		return (-1);
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**allocate_new_env(int env_size)
{
	char	**new_env;

	new_env = (char **)malloc(sizeof(char *) * (env_size + 2));
	return (new_env);
}

static void	copy_env_to_new(char **new_env, char **old_env, int env_size)
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		new_env[i] = old_env[i];
		i++;
	}
}

int	add_to_env(t_mini *mini, char *arg)
{
	int		env_size;
	char	**new_env;

	env_size = 0;
	while (mini->env && mini->env[env_size])
		env_size++;
	new_env = allocate_new_env(env_size);
	if (!new_env)
		return (1);
	copy_env_to_new(new_env, mini->env, env_size);
	new_env[env_size] = ft_strdup(arg);
	new_env[env_size + 1] = NULL;
	free(mini->env);
	mini->env = new_env;
	return (0);
}
