/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:06:17 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/30 20:09:49 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_ex(char *cmd)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

void	loop_env(t_env *new, t_env **all_env, int pos_egal)
{
	t_env	*tmp;
	int		find;

	if (!(*all_env))
	{
		*all_env = new;
		return ;
	}
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
	int		flag;

	flag = 0;
	if (cmd->cmd_param[1] == NULL)
		return (print_env(*all_env));
	i = 1;
	while (cmd->cmd_param[i])
	{
		new = build_node(i, cmd, &pos_egal);
		if (!new)
		{
			print_error_ex(cmd->cmd_param[i]);
			i++;
			flag = 1;
			continue ;
		}
		loop_env(new, all_env, pos_egal);
		i++;
	}
	return (flag);
}
