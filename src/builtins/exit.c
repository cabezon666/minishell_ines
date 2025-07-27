/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:39 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 18:45:13 by ewiese-m         ###   ########.fr       */
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

static long	ft_atol_exit(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	get_exit_code(t_mini *mini, char **args)
{
	long	exit_value;

	if (!args[1])
		return (mini->exit_code);
	if (!is_valid_number(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	exit_value = ft_atol_exit(args[1]);
	return ((int)(exit_value % 256 + 256) % 256);
}

void	ft_exit(t_mini *mini, char **args, char *input)
{
	int	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	exit_code = get_exit_code(mini, args);
	if (exit_code == -1)
	{
		mini->exit_code = 1;
		return ;
	}
	cleanup(mini, &input);
	exit(exit_code);
}
