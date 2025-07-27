/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:44:54 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_path_var(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	return (i);
}

char	**get_path(char **envp)
{
	char	*path_var;
	char	**path_dirs;
	int		i;

	i = find_path_var(envp);
	if (!envp[i])
		return (NULL);
	path_var = envp[i] + 5;
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);
	return (path_dirs);
}
