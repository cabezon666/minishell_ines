/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakkerma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:44:07 by lakkerma          #+#    #+#             */
/*   Updated: 2024/10/24 13:44:09 by lakkerma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = nmemb * size;
	if (nmemb != 0 && total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
/*
int main(void)
{
	int num = 2;
	int *array;
	
	array = (int *)ft_calloc(num, sizeof(int));
	if (array == NULL)
	{
		printf("Memory allocation has failed\n");
		return (1);
	}
	printf("Initial values in the array:\n");
	for  (int i = 0; i < num; i++)
		printf("%d", array[1]);
	printf("\n");
	free(array);
	return (0);
}*/
