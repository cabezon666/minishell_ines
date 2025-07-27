/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:19 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	should_execute_single_builtin(t_mini *mini)
{
	t_cmd	*current;

	current = mini->cmd;
	return (!current->next && is_builtin(mini)
		&& is_state_builtin(current->first_cmd));
}

static void	handle_parent_pipes(int prev_pipe_in, t_cmd *current, int *pipes)
{
	if (prev_pipe_in != -1)
		close(prev_pipe_in);
	if (current->next)
		close(pipes[1]);
}

static int	create_child_process(t_pipe_data *data, int *pipes)
{
	pid_t			pid;
	t_child_data	child_data;

	if (data->current->next && pipe(pipes) < 0)
		return (error_message("Pipe error before forking\n"));
	pid = fork();
	if (pid < 0)
		return (error_message("Pipe error after forking\n"));
	if (pid == 0)
	{
		child_data.mini = data->mini;
		child_data.current = data->current;
		child_data.input = data->input;
		child_data.prev_pipe_in = data->prev_pipe_in;
		execute_child_process(&child_data, pipes);
	}
	return (0);
}

static int	execute_pipeline(t_mini *mini, char *input)
{
	int			pipes[2];
	t_cmd		*current;
	t_pipe_data	data;

	data.mini = mini;
	data.input = input;
	data.prev_pipe_in = -1;
	current = mini->cmd;
	while (current)
	{
		data.current = current;
		if (create_child_process(&data, pipes))
			return (1);
		handle_parent_pipes(data.prev_pipe_in, current, pipes);
		if (current->next)
			data.prev_pipe_in = pipes[0];
		current = current->next;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

int	execute(t_mini *mini, char *input)
{
	if (!mini || !mini->cmd)
		return (error_message("no command\n"));
	if (should_execute_single_builtin(mini))
		return (execute_single_builtin(mini, input));
	return (execute_pipeline(mini, input));
}
