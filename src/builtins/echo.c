/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:06:07 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 17:46:53 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_mini *mini, char **arg)
{
	int i;
	int nl;

	i = 1;
	nl = 1;
	(void)mini;

	while (arg[i] && is_n_flag(arg[i]))
	{
		nl = 0;
		i++;
	}

	while (arg[i])
	{
		if (write(STDOUT_FILENO, arg[i], ft_strlen(arg[i])) == -1)
			return (1);
		if (arg[i + 1] && write(STDOUT_FILENO, " ", 1) == -1)
			return (1);
		i++;
	}

	if (nl && write(STDOUT_FILENO, "\n", 1) == -1)
		return (1);
	return (0);
}