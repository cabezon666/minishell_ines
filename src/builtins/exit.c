/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:39 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 17:31:10 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	get_exit_code(char **args)
{
	if (!args[1])
		return (0);
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	if (!is_valid_number(args[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	return (ft_atoi(args[1]) & 255);
}

void	ft_exit(t_mini *mini, char **args, char *input)
{
	int	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	exit_code = get_exit_code(args);
	if (exit_code == -1)
	{
		mini->exit_code = 1;
		return ;
	}
	cleanup(mini, &input);
	exit(exit_code);
}
