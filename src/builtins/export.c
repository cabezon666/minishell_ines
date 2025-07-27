/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:08:29 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 17:45:41 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	valid_identifier(const char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
		return (0);
	if (arg[0] == '=')
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	update_existing_var(t_mini *mini, int pos, char *new_var)
{
	free(mini->env[pos]);
	mini->env[pos] = new_var;
	return (0);
}

static int	process_var_assignment(t_mini *mini, char *arg, char *eq)
{
	int		pos;
	char	*value;
	char	*new_var;

	*eq = '\0';
	pos = find_env_var(mini->env, arg);
	value = eq + 1;
	new_var = ft_strjoin3(arg, "=", value);
	*eq = '=';
	if (pos != -1)
	{
		return (update_existing_var(mini, pos, new_var));
	}
	else if (add_to_env(mini, new_var))
	{
		free(new_var);
		return (1);
	}
	else
	{
		free(new_var);
	}
	return (0);
}

int	ft_export(t_mini *mini, char **args)
{
	int i;
	char *eq;
	int exit_code;

	i = 1;
	exit_code = 0;
	if (!args[1])
		return (export_no_args(mini));
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_code = 1;
		}
		else
		{
			eq = ft_strchr(args[i], '=');
			if (eq)
			{
				if (process_var_assignment(mini, args[i], eq))
					exit_code = 1;
			}
		}
		i++;
	}
	return (exit_code);
}