/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:28:46 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/30 20:16:30 by sdiakho          ###   ########.fr       */
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

int	alloc_name(t_env *env, char *str)
{
	char	*name;

	if (!str)
		return (0);
	name = ft_strnndup(str, 0, ft_strlen(str));
	if (!name)
		return (0);
	env->name = name;
	env->value = NULL;
	return (1);
}

int	alloc_env(t_env *env, char *str, int sep)
{
	int		len;
	char	*name;
	char	*value;

	len = ft_strlen(str);
	name = ft_strnndup(str, 0, sep);
	if (!name)
		return (0);
	value = ft_strnndup(str, sep + 1, len);
	if (!value)
		return (free(name), 0);
	env->name = name;
	env->value = value;
	return (1);
}

int	init_shlvl(t_env **all_env)
{
	char	*value;
	int		int_value;

	int_value = 0;
	value = get_env_value(ft_strnndup("SHLVL", 0, 5), (*all_env));
	ft_atoi(value, &int_value);
	free(value);
	int_value++;
	value = ft_itoa(int_value);
	if (!value)
		return (0);
	if (!update_path("SHLVL=", value, all_env))
	{
		ft_putstr_fd("minishell: SHLVL error", 2);
		free(value);
		return (0);
	}
	free(value);
	return (1);
}
