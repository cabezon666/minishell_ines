/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:02:01 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/23 13:02:02 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	symb;
	int	result;

	symb = 1;
	result = 0;
	while (*nptr != '\0' && ((*nptr >= 9 && *nptr <= 13) || *nptr == 32))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			symb = -symb;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * symb);
}
/*
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		return (1);
	}
	int result = ft_atoi(argv[1]);
	printf("%d\n", result);
	return (0);
}*/
