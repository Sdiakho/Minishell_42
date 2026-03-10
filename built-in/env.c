/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:03:17 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/07 17:46:39 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_env(char **envp, t_env **all_env)
{
	int		i;
	int		sep;
	t_env	*tmp;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		tmp = create_node_env();
		if (!tmp)
			return (clean_env(all_env), 0);
		sep = search_key(envp[i]);
		if (sep == -1)
		{
			if (!alloc_name(&tmp, envp[i]))
				return (clean_env(all_env), free(tmp), 0);
		}
		else
			if (!alloc_env(&tmp, envp[i], sep))
				return (clean_env(all_env), free(tmp), 0);
		add_front_env(all_env, tmp);
		i++;
	}
	return (1);
}

int	ft_env(t_env **all_env)
{
	t_env	*tmp;

	if (!all_env)
		return (0);
	tmp = *all_env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}
