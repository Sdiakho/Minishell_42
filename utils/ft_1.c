/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:49:59 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/28 09:23:38 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnndup(char *src, int start, int end)
{
	int		i;
	int		len;
	char	*dup;

	len = ft_strlen(src);
	dup = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		dup[i] = src[start + i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
