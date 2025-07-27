/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:54:47 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:06 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*env_value(t_mini *mini, char *var_name)
{
	int		i;
	size_t	len;
	char	*env_var;
	char	*exit_status;

	if (!var_name || !mini->env)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
	{
		exit_status = ft_itoa(mini->exit_code);
		return (exit_status);
	}
	len = ft_strlen(var_name);
	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], var_name, len) == 0
			&& mini->env[i][len] == '=')
		{
			env_var = ft_strdup(mini->env[i] + len + 1);
			return (env_var);
		}
		i++;
	}
	return (ft_strdup(""));
}

void	expand_cmd_args(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*expanded;

	if (!cmd || !cmd->split_cmd)
		return ;
	i = 0;
	while (cmd->split_cmd[i])
	{
		expanded = expand_env_vars(mini, cmd->split_cmd[i]);
		if (expanded)
		{
			free(cmd->split_cmd[i]);
			cmd->split_cmd[i] = expanded;
		}
		i++;
	}
}
