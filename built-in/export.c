/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:06:17 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/26 18:42:39 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop_env(t_env *new, t_env **all_env, int pos_egal)
{
	t_env	*tmp;
	int		find;

	find = 0;
	tmp = *all_env;
	while (tmp->next)
	{
		if (process_node(tmp, new, pos_egal))
		{
			find = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (find != 1)
		if (!process_node(tmp, new, pos_egal))
			tmp->next = new;
}

int	ft_export(t_cmd *cmd, t_env **all_env)
{
	int		i;
	int		pos_egal;
	t_env	*new;

	if (cmd->cmd_param[1] == NULL)
	{
		print_env(*all_env);
		return (0);
	}
	i = 1;
	while (cmd->cmd_param[i])
	{
		new = build_node(&i, cmd, &pos_egal, all_env);
		if (!new)
			continue ;
		loop_env(new, all_env, pos_egal);
		i++;
	}
	return (0);
}
