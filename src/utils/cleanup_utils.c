/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:45:38 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_per_command(t_mini *mini)
{
	if (!mini)
		return ;
	free_list_cmd(&mini->cmd);
	mini->fd = 0;
	mini->exit_code = 0;
}

static void	close_mini_fd(t_mini *mini)
{
	if (mini->fd > 0)
	{
		close(mini->fd);
		mini->fd = 0;
	}
}

void	free_mini(t_mini *mini)
{
	if (!mini)
		return ;
	free_list_cmd(&mini->cmd);
	free_list(&mini->env);
	free_list(&mini->path);
	mini->path = NULL;
	close_mini_fd(mini);
}
