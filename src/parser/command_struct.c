/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:16 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:45:11 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*alloc_cmd_and_set_full(char *command)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->full_cmd = ft_strdup(command);
	if (!cmd->full_cmd)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redirec = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	handle_split_cmd(t_cmd *cmd, t_mini *mini, char *command)
{
	cmd->split_cmd = split_args_quote_aware(mini, command);
	if (!cmd->split_cmd)
	{
		free(cmd->full_cmd);
		free(cmd);
		return (1);
	}
	return (0);
}

int	handle_first_cmd(t_cmd *cmd)
{
	if (cmd->split_cmd[0])
	{
		cmd->first_cmd = ft_strdup(cmd->split_cmd[0]);
		if (!cmd->first_cmd)
		{
			free_list(&cmd->split_cmd);
			free(cmd->full_cmd);
			free(cmd);
			return (1);
		}
	}
	else
		cmd->first_cmd = NULL;
	return (0);
}

t_cmd	*create_command_structure(char **commands, t_mini *mini)
{
	t_cmd	*head;
	t_cmd	*current;
	int		error_flag;

	head = NULL;
	current = NULL;
	error_flag = build_command_list(commands, mini, &head, &current);
	if (error_flag)
	{
		free_list_cmd(&head);
		return (NULL);
	}
	return (head);
}
