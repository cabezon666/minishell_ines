/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:10:37 by lakkerma          #+#    #+#             */
/*   Updated: 2024/11/05 12:10:38 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_buffer(int fd, char **saved, char *buffer)
{
	int		bytes_read;
	char	*temp;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0 || buffer == NULL)
	{
		free(*saved);
		*saved = (NULL);
		return (-1);
	}
	if (bytes_read == 0)
		return (0);
	temp = ft_strjoin(*saved, buffer);
	free(*saved);
	*saved = temp;
	return (bytes_read);
}

static void	extract_line(char **saved, char **line)
{
	char	*n;
	size_t	len;
	size_t	i;

	n = ft_strchr(*saved, '\n');
	len = ft_strlen(*saved) - ft_strlen(n) + 2;
	*line = (char *)malloc(len * sizeof(char));
	if (!line)
		return ;
	i = 0;
	while (i < len - 1)
	{
		(*line)[i] = (*saved)[i];
		i++;
	}
	(*line)[i] = '\0';
}

static void	remove_line(char **saved)
{
	char	*n;
	char	*temp;

	n = ft_strchr(*saved, '\n');
	if (!n)
	{
		free(*saved);
		*saved = NULL;
		return ;
	}
	temp = ft_strdup(n + 1);
	if (!temp)
	{
		free(*saved);
		*saved = NULL;
		return ;
	}
	free(*saved);
	*saved = temp;
	if (**saved == '\0')
	{
		free(*saved);
		*saved = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;
	char		*buffer;
	int			byte;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	byte = 1;
	while (ft_strchr(saved, '\n') == NULL && byte > 0)
		byte = read_buffer(fd, &saved, buffer);
	free(buffer);
	if (byte == -1)
		return (NULL);
	if (ft_strlen(saved) == 0)
		return (NULL);
	extract_line(&saved, &line);
	remove_line(&saved);
	return (line);
}
