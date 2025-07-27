/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:10:17 by lakkerma          #+#    #+#             */
/*   Updated: 2025/06/04 10:10:20 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *src, const char *dest)
{
	while (*src == *dest && *src && *dest)
	{
		src++;
		dest++;
	}
	return (*src - *dest);
}
