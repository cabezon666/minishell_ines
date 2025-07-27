/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:23 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	create_heredoc_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("minishell");
		return (0);
	}
	return (1);
}

static void	write_line_to_pipe(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	read_heredoc_lines(int *fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_line_to_pipe(fd[1], line);
		free(line);
	}
	return (1);
}

static void	setup_heredoc_input(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

int	handle_heredoc(char *delimiter)
{
	int	fd[2];

	if (!create_heredoc_pipe(fd))
		return (0);
	if (!read_heredoc_lines(fd, delimiter))
		return (0);
	setup_heredoc_input(fd);
	return (1);
}
