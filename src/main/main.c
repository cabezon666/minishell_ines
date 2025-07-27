/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:50 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_empty_input(char *input)
{
	if (input == NULL)
	{
		write(1, "\n", 1);
		return (1);
	}
	if (*input == '\0' || ft_strisspace(input))
	{
		free(input);
		return (2);
	}
	return (0);
}

static void	process_input(t_mini *mini, char *input)
{
	if (*input)
	{
		add_history(input);
		parser(mini, input);
		execute(mini, input);
	}
}

static void	cleanup_and_exit(t_mini *mini, char *input)
{
	rl_clear_history();
	cleanup(mini, &input);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*input;
	int		status;

	init_mini(&mini, argc, argv, envp);
	while (mini.ready)
	{
		input = readline("🪩 la minishellita💃:> ");
		status = handle_empty_input(input);
		if (status == 1)
		{
			mini.exit_code = 0;
			break ;
		}
		if (status == 2)
			continue ;
		process_input(&mini, input);
		free(input);
		input = NULL;
		free_per_command(&mini);
	}
	cleanup_and_exit(&mini, input);
	return (mini.exit_code);
}
