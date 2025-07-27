/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:35 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_input_redir(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

static int	handle_output_redir(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	handle_append_redir(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	process_redirection(t_redir *redir)
{
	if (redir->type == IN_REDIR)
		return (handle_input_redir(redir->filename));
	else if (redir->type == OUT_REDIR)
		return (handle_output_redir(redir->filename));
	else if (redir->type == APPEND_REDIR)
		return (handle_append_redir(redir->filename));
	else if (redir->type == HEREDOC_REDIR)
		return (handle_heredoc(redir->filename));
	return (1);
}

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirec;
	while (redir)
	{
		if (!process_redirection(redir))
			return (0);
		redir = redir->next;
	}
	return (1);
}
