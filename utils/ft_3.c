/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:12:53 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/10 13:28:15 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strschr(char *str, char *chr)
{
	int	i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (chr[j])
		{
			if (str[i + j] == chr[j])
				j++;
			else 
				break ;
		}
		if (j == ft_strlen(chr))
			return (1);
		i++;
	}
	return (0);
}
