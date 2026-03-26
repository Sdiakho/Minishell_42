/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:12:01 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/26 18:43:14 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*repair_token(char *token, int pos_egal)
{
	token[pos_egal] = '=';
	return (NULL);
}

t_env	*create_partial_node(char *token)
{
	int		len_name;
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	len_name = ft_strlen(token) + 1;
	new->name = (char *)malloc(len_name);
	if (!new->name)
		return (free(new), NULL);
	ft_strlcopy(new->name, token, len_name + 1);
	new->value = NULL;
	new->next = NULL;
	return (new);
}

t_env	*create_full_node(char *token, int pos_egal)
{
	int		len_value;
	t_env	*new;

	token[pos_egal] = '\0';
	if (!check_var(token))
		return (repair_token(token, pos_egal));
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (repair_token(token, pos_egal));
	new->name = (char *)malloc(pos_egal + 1);
	if (!new->name)
		return (free(new), repair_token(token, pos_egal));
	new->value = (char *)malloc(ft_strlen(&(token[pos_egal + 1])) + 1);
	if (!new->value)
		return (free(new->name), free(new), repair_token(token, pos_egal));
	ft_strlcopy(new->name, token, pos_egal + 1);
	len_value = ft_strlen(&(token[pos_egal + 1])) + 1;
	ft_strlcopy(new->value, &(token[pos_egal + 1]), len_value + 1);
	token[pos_egal] = '=';
	new->next = NULL;
	return (new);
}

int	process_node(t_env *tmp, t_env *new, int pos_egal)
{
	if (!ft_strncmp(tmp->name, new->name, ft_strlen(new->name) + 1))
	{
		if (pos_egal != -1)
		{
			free(tmp->value);
			tmp->value = new->value;
		}
		free(new->name);
		free(new);
		return (1);
	}
	else
		return (0);
}

t_env	*build_node(int *i, t_cmd *cmd, int *pos_egal, t_env **all_env)
{
	t_env	*new;

	*pos_egal = ft_strchr(cmd->cmd_param[*i], '=');
	if (*pos_egal == -1)
		new = create_partial_node(cmd->cmd_param[*i]);
	else
		new = create_full_node(cmd->cmd_param[*i], *pos_egal);
	if (!new)
	{
		(*i)++;
		return (NULL);
	}
	if (*all_env == NULL)
	{
		*all_env = new;
		(*i)++;
		return (NULL);
	}
	return (new);
}
