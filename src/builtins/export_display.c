/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:43:31 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_bubble(char **sorted_env, int count)
{
	int		i;
	char	*temp;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(sorted_env[i], sorted_env[i + 1]) > 0)
			{
				temp = sorted_env[i];
				sorted_env[i] = sorted_env[i + 1];
				sorted_env[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}

static char	**create_sorted_copy(t_mini *mini, int count)
{
	char	**sorted_env;
	int		i;

	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (mini->env[i])
	{
		sorted_env[i] = mini->env[i];
		i++;
	}
	sorted_env[i] = NULL;
	ft_bubble(sorted_env, count);
	return (sorted_env);
}

static void	print_env_vars(char **sorted_env)
{
	int	i;

	i = 0;
	while (sorted_env[i])
	{
		ft_printf("%s\n", sorted_env[i]);
		i++;
	}
}

int	export_no_args(t_mini *mini)
{
	int		count;
	char	**sorted_env;

	count = 0;
	if (mini->env == NULL)
	{
		write(2, "No env var set\n", 15);
		return (0);
	}
	while (mini->env[count])
		count++;
	sorted_env = create_sorted_copy(mini, count);
	if (!sorted_env)
		return (1);
	print_env_vars(sorted_env);
	free(sorted_env);
	return (1);
}
