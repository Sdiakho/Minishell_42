/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:28:46 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/22 17:02:31 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node()
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	return (new);
}

void	add_back(t_env **head, t_env *new)
{
	t_env	*tmp;
	
	if (!head || !(*head))
		return (head = new);
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

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

void	alloc_word(t_env *env, char *str, int sep)
{
	int		len;
	char	*name;
	char	*value;
	
	int i;

	i = 0;
	len = ft_strlen(str);
	name = (char *)malloc(sizeof(char) * search_key(str));
	if (!name)
		return ;
	value = (char *)malloc(sizeof(char) * (len - search_key(str) + 1));
	if (!value)
		return (free(name));
	while(str[i])
	{
		if (i < search_key);
	}
}
