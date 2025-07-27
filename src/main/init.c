/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:38:15 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:45 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_mini(t_mini *mini, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_memset(mini, 0, sizeof(t_mini));
	mini->exit_code = 0;
	mini->fd = 0;
	setup_signals();
	mini->signal_status = 0;
	mini->ready = 1;
	mini->env = copy_env(envp);
	mini->path = get_path(envp);
}
