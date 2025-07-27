/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:39 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:45:25 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_redir_type	get_direction(char *token)
{
	if (!token)
		return (NO_REDIR);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND_REDIR);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (HEREDOC_REDIR);
	if (ft_strncmp(token, "<", 1) == 0)
		return (IN_REDIR);
	if (ft_strncmp(token, ">", 1) == 0)
		return (OUT_REDIR);
	return (NO_REDIR);
}

static void	add_redir(t_cmd *cmd, t_redir_type type, char *filename)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->filename = ft_strdup(filename);
	if (!new_redir->filename)
	{
		free(new_redir);
		return ;
	}
	new_redir->next = NULL;
	if (!cmd->redirec)
	{
		cmd->redirec = new_redir;
	}
	else
	{
		current = cmd->redirec;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

static int	handle_redirection(t_cmd *cmd, t_redir_type type, int *i)
{
	if (!cmd->split_cmd[*i + 1])
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n",
			STDERR_FILENO);
		return (1);
	}
	add_redir(cmd, type, cmd->split_cmd[*i + 1]);
	free(cmd->split_cmd[*i]);
	free(cmd->split_cmd[*i + 1]);
	*i += 2;
	return (0);
}

static void	move_non_redir_token(t_cmd *cmd, int *i, int *j)
{
	if (*i != *j)
	{
		cmd->split_cmd[*j] = cmd->split_cmd[*i];
		cmd->split_cmd[*i] = NULL;
	}
	(*j)++;
	(*i)++;
}

void	process_redir(t_cmd *cmd)
{
	int				i;
	int				j;
	t_redir_type	type;

	i = 0;
	j = 0;
	while (cmd->split_cmd && cmd->split_cmd[i])
	{
		type = get_direction(cmd->split_cmd[i]);
		if (type != NO_REDIR)
		{
			if (handle_redirection(cmd, type, &i))
				return ;
		}
		else
			move_non_redir_token(cmd, &i, &j);
	}
	if (cmd->split_cmd)
		cmd->split_cmd[j] = NULL;
}
