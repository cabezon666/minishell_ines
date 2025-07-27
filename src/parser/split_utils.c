/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inpastor <inpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:19:33 by inpastor          #+#    #+#             */
/*   Updated: 2025/07/27 14:45:33 by inpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_tokens_between_pipes(char *line)
{
	int		count;
	char	in_quote;

	count = 1;
	in_quote = 0;
	while (*line)
	{
		if (!in_quote && *line == '|')
			count++;
		else if (*line == '\'' || *line == '"')
		{
			if (in_quote == 0)
				in_quote = *line;
			else if (in_quote == *line)
				in_quote = 0;
		}
		line++;
	}
	return (count);
}

static char	*extract_single_command(char *line, int *i)
{
	int		start;
	char	in_quote;
	int		end;
	char	*cmd;

	start = *i;
	in_quote = 0;
	while (line[*i] && (in_quote || line[*i] != '|'))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (in_quote == 0)
				in_quote = line[*i];
			else if (in_quote == line[*i])
				in_quote = 0;
		}
		(*i)++;
	}
	end = *i;
	while (end > start && ft_isspace(line[end - 1]))
		end--;
	cmd = ft_substr(line, start, end - start);
	if (line[*i] == '|')
		(*i)++;
	return (cmd);
}

static void	free_command_array(char **cmd_arr, int count)
{
	while (count-- > 0)
		free(cmd_arr[count]);
	free(cmd_arr);
}

char	**split_commands(char *line)
{
	int		cmd_count;
	char	**cmd_arr;
	int		i;
	int		j;

	if (!line || !*line)
		return (NULL);
	cmd_count = count_tokens_between_pipes(line);
	cmd_arr = malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (j < cmd_count)
	{
		cmd_arr[j] = extract_single_command(line, &i);
		if (!cmd_arr[j])
		{
			free_command_array(cmd_arr, j);
			return (NULL);
		}
		j++;
	}
	cmd_arr[j] = NULL;
	return (cmd_arr);
}
