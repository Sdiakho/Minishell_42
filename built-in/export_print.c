/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:07:35 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/26 18:09:48 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_len(t_env *all_env)
{
	int	count;

	count = 0;
	while (all_env)
	{
		count++;
		all_env = all_env->next;
	}
	return (count);
}

int	envcmp(t_env *s1, t_env *s2)
{
	int	i;

	i = 0;
	while (s1->name[i] && s2->name[i] && s1->name[i] == s2->name[i])
		i++;
	return (s1->name[i] - s2->name[i]);
}

void	fill_tab(t_env **tab, t_env *all_env)
{
	int	i;

	i = 0;
	while (all_env)
	{
		tab[i] = all_env;
		i++;
		all_env = all_env->next;
	}
}

void	sort_tab(t_env **tab, int env_len)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < env_len)
	{
		j = 0;
		while (j < env_len - 1)
		{
			if (envcmp(tab[j], tab[j + 1]) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	*print_env(t_env *all_env)
{
	int		i;
	int		len_env;
	t_env	**tab;

	i = 0;
	len_env = env_len(all_env);
	tab = malloc(sizeof(t_env *) * len_env);
	if (!tab)
		return (NULL);
	fill_tab(tab, all_env);
	i = 0;
	sort_tab(tab, len_env);
	while (i < len_env)
	{
		printf("declare -x %s", tab[i]->name);
		if (tab[i]->value)
			printf("=\"%s\"", tab[i]->value);
		printf("\n");
		i++;
	}
	free(tab);
	return (NULL);
}
