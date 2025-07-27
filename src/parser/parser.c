/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:25 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:45:15 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	validate_quotes(const char *line)
{
	char	in_quote;

	in_quote = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '"')
		{
			if (in_quote == 0)
				in_quote = *line;
			else if (in_quote == *line)
				in_quote = 0;
		}
		line++;
	}
	if (in_quote)
	{
		ft_putstr_fd("syntax error: unclosed quote\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	parser(t_mini *mini, char *line)
{
	char	**commands;

	if (!validate_quotes(line))
	{
		mini->exit_code = 2;
		return ;
	}
	free_list_cmd(&mini->cmd);
	commands = split_commands(line);
	if (!commands)
	{
		mini->exit_code = 1;
		return ;
	}
	mini->cmd = create_command_structure(commands, mini);
	free_list(&commands);
	commands = NULL;
	if (!mini->cmd)
		mini->exit_code = 1;
}
