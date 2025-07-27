/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 18:45:50 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_mini *mini)
{
	char	*cmd;

	if (!mini || !mini->cmd || !mini->cmd->first_cmd)
		return (0);
	cmd = mini->cmd->first_cmd;
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static int	execute_builtin_part2(t_mini *mini, t_cmd *cmd, char *input)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd->first_cmd, "pwd") == 0)
		ret = ft_pwd(mini);
	else if (ft_strcmp(cmd->first_cmd, "unset") == 0)
		ret = ft_unset(mini, cmd->split_cmd);
	else if (ft_strcmp(cmd->first_cmd, "exit") == 0)
	{
		ft_exit(mini, cmd->split_cmd, input);
		ret = mini->exit_code;
	}
	return (ret);
}

static int	execute_builtin_part1(t_mini *mini, t_cmd *cmd, char *input)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd->first_cmd, "cd") == 0)
		ret = ft_cd(mini, cmd->split_cmd);
	else if (ft_strcmp(cmd->first_cmd, "echo") == 0)
		ret = ft_echo(mini, cmd->split_cmd);
	else if (ft_strcmp(cmd->first_cmd, "env") == 0)
		ret = ft_env(mini, cmd->split_cmd);
	else if (ft_strcmp(cmd->first_cmd, "export") == 0)
		ret = ft_export(mini, cmd->split_cmd);
	else
		ret = execute_builtin_part2(mini, cmd, input);
	return (ret);
}

int	execute_builtin(t_mini *mini, t_cmd *cmd, char *input)
{
	int	ret;
	int	old_exit_code;

	old_exit_code = mini->exit_code;
	ret = execute_builtin_part1(mini, cmd, input);
	if (ft_strcmp(cmd->first_cmd, "exit") == 0 && ret == old_exit_code)
	{
		return (ret);
	}
	mini->exit_code = ret;
	return (ret);
}

int	is_state_builtin(const char *cmd)
{
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"));
}
