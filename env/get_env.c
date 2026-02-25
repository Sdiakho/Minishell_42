/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:28:46 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/25 12:10:46 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_key(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	alloc_name(t_env **env, char *str)
{
	char	*name;

	if (!str)
		return ;
	name = ft_strnndup(str, 0, ft_strlen(str));
	(*env)->name = name;
	(*env)->value = NULL;
}

void	alloc_env(t_env **env, char *str, int sep)
{
	int		len;
	char	*name;
	char	*value;

	len = ft_strlen(str);
	name = ft_strnndup(str, 0, sep);
	value = ft_strnndup(str, sep + 1, len);
	(*env)->name = name;
	(*env)->value = value;
}
