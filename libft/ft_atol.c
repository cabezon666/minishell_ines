/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:11:11 by lakkerma          #+#    #+#             */
/*   Updated: 2025/04/07 11:11:14 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static long	handle_overflow(int sign)
{
	if (sign == 1)
		return (LONG_MAX);
	else
		return (LONG_MIN);
}

static long	process_digits(const char *str, long result, int sign)
{
	while (ft_isdigit(*str))
	{
		if (result > (LONG_MAX / 10) || (result == (LONG_MAX / 10)
				&& (*str - '0') > (LONG_MAX % 10)))
			return (handle_overflow(sign));
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (process_digits(str, result, sign));
}
