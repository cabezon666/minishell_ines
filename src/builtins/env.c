/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:06:09 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:43:03 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_mini *mini, char **args)
{
	int	i;

	i = 0;
	ft_printf("");
	if (!mini->env)
	{
		ft_putstr_fd("env: environment not set\n", STDERR_FILENO);
		return (1);
	}
	if (args[1])
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	while (mini->env[i])
	{
		if (ft_strchr(mini->env[i], '=') != NULL)
		{
			ft_putendl_fd(mini->env[i], STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
