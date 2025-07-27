/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_struct_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:16 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:45:07 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	process_one_command(t_cmd **new_cmd, char *command, t_mini *mini)
{
	int	error_flag;

	error_flag = 0;
	*new_cmd = alloc_cmd_and_set_full(command);
	if (!*new_cmd)
		error_flag = 1;
	if (!error_flag && handle_split_cmd(*new_cmd, mini, command))
		error_flag = 1;
	if (!error_flag)
		process_redir(*new_cmd);
	if (!error_flag && handle_first_cmd(*new_cmd))
		error_flag = 1;
	return (error_flag);
}

static void	link_command_to_list(t_cmd **head, t_cmd **current, t_cmd *new_cmd)
{
	if (!*head)
	{
		*head = new_cmd;
		*current = new_cmd;
	}
	else
	{
		(*current)->next = new_cmd;
		*current = new_cmd;
	}
}

int	build_command_list(char **commands, t_mini *mini, t_cmd **head,
		t_cmd **current)
{
	t_cmd	*new_cmd;
	int		i;
	int		error_flag;

	new_cmd = NULL;
	i = 0;
	error_flag = 0;
	while (commands[i] && !error_flag)
	{
		error_flag = process_one_command(&new_cmd, commands[i], mini);
		if (!error_flag)
			link_command_to_list(head, current, new_cmd);
		i++;
	}
	return (error_flag);
}
