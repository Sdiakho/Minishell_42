/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:10:44 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/04 13:17:41 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*new_ptr;

	total_size = count * size;
	if (total_size == 0)
		return (NULL);
	new_ptr = (char *)malloc(total_size);
	if (!new_ptr)
		return (NULL);
	ft_bzero(new_ptr, total_size);
	return (new_ptr);
}
