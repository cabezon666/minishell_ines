/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:25 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:45:02 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_parse_state(char c, t_parse_state *state)
{
	if (*state == STATE_NORMAL)
	{
		if (c == '\'')
			*state = STATE_IN_SINGLE_QUOTE;
		else if (c == '"')
			*state = STATE_IN_DOUBLE_QUOTE;
	}
	else if (*state == STATE_IN_SINGLE_QUOTE)
	{
		if (c == '\'')
			*state = STATE_NORMAL;
	}
	else if (*state == STATE_IN_DOUBLE_QUOTE)
	{
		if (c == '"')
			*state = STATE_NORMAL;
	}
}

static char	**finalize_args(char **args, int error_flag, int arg_count)
{
	if (error_flag)
	{
		free_list(&args);
		return (NULL);
	}
	args[arg_count] = NULL;
	return (args);
}

static int	process_space_token(t_mini *mini, char *cmd_str, t_parse_data *data,
		char **args)
{
	char	*arg;

	if (data->i > data->start)
	{
		arg = process_arg(mini, cmd_str + data->start, data->i - data->start);
		if (!arg)
			return (1);
		args[data->arg_count++] = arg;
	}
	data->start = data->i + 1;
	return (0);
}

static int	process_final_token(t_mini *mini, char *cmd_str, t_parse_data *data,
		char **args)
{
	char	*arg;

	if (data->i > data->start)
	{
		arg = process_arg(mini, cmd_str + data->start, data->i - data->start);
		if (!arg)
			return (1);
		args[data->arg_count++] = arg;
	}
	return (0);
}

char	**split_args_quote_aware(t_mini *mini, char *cmd_str)
{
	char			**args;
	t_parse_data	data;

	data.i = 0;
	data.arg_count = 0;
	data.state = STATE_NORMAL;
	data.start = 0;
	data.error_flag = 0;
	args = malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (!args)
		return (NULL);
	ft_memset(args, 0, sizeof(char *) * (MAX_ARGS + 1));
	while (cmd_str[data.i] && data.arg_count < MAX_ARGS && !data.error_flag)
	{
		update_parse_state(cmd_str[data.i], &data.state);
		if (data.state == STATE_NORMAL && ft_isspace(cmd_str[data.i]))
			data.error_flag = process_space_token(mini, cmd_str, &data, args);
		data.i++;
	}
	if (!data.error_flag)
		data.error_flag = process_final_token(mini, cmd_str, &data, args);
	return (finalize_args(args, data.error_flag, data.arg_count));
}
