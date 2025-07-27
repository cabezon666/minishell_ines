/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 15:09:38 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_list(char ***path)
{
	int	i;

	i = 0;
	if (!path || !*path)
		return ;
	while ((*path)[i])
	{
		free((*path)[i]);
		(*path)[i] = NULL;
		i++;
	}
	free(*path);
	*path = NULL;
}

void	free_redir_list(t_redir **redir)
{
	t_redir	*temp;

	if (!redir || !*redir)
		return ;
	while (*redir)
	{
		temp = *redir;
		*redir = (*redir)->next;
		free(temp->filename);
		temp->filename = NULL;
		free(temp);
	}
}

static void	free_cmd_strings(t_cmd *cmd)
{
	free(cmd->full_cmd);
	cmd->full_cmd = NULL;
	free_list(&cmd->split_cmd);
	cmd->split_cmd = NULL;
	free(cmd->first_cmd);
	cmd->first_cmd = NULL;
	free_redir_list(&cmd->redirec);
	cmd->redirec = NULL;
}

void	free_list_cmd(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd)
		return ;
	current = *cmd;
	while (current)
	{
		next = current->next;
		free_cmd_strings(current);
		free(current);
		current = next;
	}
	*cmd = NULL;
}

void	cleanup(t_mini *mini, char **input)
{
	if (input && *input)
	{
		free(*input);
		*input = NULL;
	}
	free_mini(mini);
	mini = NULL;
}
