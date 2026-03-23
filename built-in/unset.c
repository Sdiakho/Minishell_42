/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:52:05 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/23 20:57:39 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var(char *var)
{
	int	i;

	i = 0;
	if (var[0] >= '0' && var[0] <= '9')
		return (0);
	while (var[i])
	{
		if (!is_alnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	free_node(t_env *node)
{
	free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	process_node(char *cmd, t_env **all_env)
{
	t_env	*current;
	t_env	*prev;

	current = *all_env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(cmd, current->name, ft_strlen(cmd) + 1) == 0)
		{
			if (prev == NULL)
				*all_env = (*all_env)->next;
			else
				prev->next = current->next;
			free_node(current);
			break ;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	print_error(char *cmd)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" not a valid identifier\n", 2);
}

int	ft_unset(t_cmd *cmd, t_env **all_env)
{
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	while (cmd->cmd_param[i])
	{
		if (!check_var(cmd->cmd_param[i]))
		{
			flag = 1;
			print_error(cmd->cmd_param[i]);
			i++;
			continue ;
		}
		process_node(cmd->cmd_param[i], all_env);
		i++;
	}
	return (flag);
}
