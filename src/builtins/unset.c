/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:07:17 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:43:52 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	valid_identifier(const char *name)
{
	int	i;

	i = 0;
	if (!name || !*name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
	}
	return (1);
}

static int	remove_env_var(t_mini *mini, char *name)
{
	int	pos;
	int	i;

	if (!valid_identifier(name))
	{
		ft_putstr_fd("unset: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd(" : not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	pos = find_env_var(mini->env, name);
	if (pos == -1)
		return (0);
	free(mini->env[pos]);
	i = pos;
	while (mini->env[i])
	{
		mini->env[i] = mini->env[i + 1];
		i++;
	}
	return (0);
}

int	ft_unset(t_mini *mini, char **args)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (args[i])
	{
		if (remove_env_var(mini, args[i]) != 0)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
