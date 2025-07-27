/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:11 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	backup_stdio(int *copy_stdin, int *copy_stdout)
{
	*copy_stdin = dup(STDIN_FILENO);
	*copy_stdout = dup(STDOUT_FILENO);
	if (*copy_stdin == -1 || *copy_stdout == -1)
		return (0);
	return (1);
}

static void	restore_stdio(int copy_stdin, int copy_stdout)
{
	dup2(copy_stdin, STDIN_FILENO);
	dup2(copy_stdout, STDOUT_FILENO);
	close(copy_stdin);
	close(copy_stdout);
}

static int	handle_single_builtin_redirections(t_cmd *current, int copy_stdin,
		int copy_stdout)
{
	if (!handle_redirections(current))
	{
		restore_stdio(copy_stdin, copy_stdout);
		return (0);
	}
	return (1);
}

int	execute_single_builtin(t_mini *mini, char *input)
{
	t_cmd	*current;
	int		copy_stdin;
	int		copy_stdout;
	int		ret;

	current = mini->cmd;
	if (!backup_stdio(&copy_stdin, &copy_stdout))
		return (1);
	if (!handle_single_builtin_redirections(current, copy_stdin, copy_stdout))
		return (1);
	expand_cmd_args(mini, current);
	ret = execute_builtin(mini, current, input);
	restore_stdio(copy_stdin, copy_stdout);
	return (ret);
}
