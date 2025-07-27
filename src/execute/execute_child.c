/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:15 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_input_pipe(int prev_pipe_in)
{
	if (prev_pipe_in != -1)
	{
		dup2(prev_pipe_in, STDIN_FILENO);
		close(prev_pipe_in);
	}
}

static int	has_output_redirection(t_cmd *current)
{
	t_redir	*r;

	r = current->redirec;
	while (r)
	{
		if (r->type == OUT_REDIR || r->type == APPEND_REDIR)
			return (1);
		r = r->next;
	}
	return (0);
}

static void	setup_output_pipe(t_cmd *current, int *pipes)
{
	if (current->next && !has_output_redirection(current))
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
	}
}

static void	execute_external_command(t_mini *mini, t_cmd *current, char *input)
{
	char	*path;

	path = get_cmd_path(mini->path, current->first_cmd);
	if (!path)
	{
		ft_putstr_fd("minishellita: ", STDERR_FILENO);
		ft_putstr_fd(current->first_cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		clean_child_exit(mini, input, 127);
	}
	execve(path, current->split_cmd, mini->env);
	perror("minishellita");
	free(path);
	clean_child_exit(mini, input, 126);
}

void	execute_child_process(t_child_data *data, int *pipes)
{
	setup_input_pipe(data->prev_pipe_in);
	setup_output_pipe(data->current, pipes);
	if (!handle_redirections(data->current))
		clean_child_exit(data->mini, data->input, 1);
	expand_cmd_args(data->mini, data->current);
	if (is_builtin(data->mini))
		clean_child_exit(data->mini, data->input, execute_builtin(data->mini,
				data->current, data->input));
	else
		execute_external_command(data->mini, data->current, data->input);
}
