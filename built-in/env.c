/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:03:17 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/25 12:06:37 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*fill_env(char **envp, t_env **all_env)
{
	int		i;
	int		sep;
	t_env	*tmp;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		tmp = create_node();
		sep = search_key(envp[i]);
		if (sep == -1)
			alloc_name(&tmp, envp[i]);
		else
			alloc_env(&tmp, envp[i], sep);
		add_front(all_env, tmp);
		i++;
	}
	return (*all_env);
}

void	env(t_env **all_env)
{
	t_env	*tmp;

	if (!all_env)
		return ;
	tmp = *all_env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	clean_env(t_env **all_env)
{
	t_env	*tmp;

	if (!all_env || !(*all_env))
		return ;
	while (*all_env)
	{
		tmp = *all_env;
		*all_env = (*all_env)->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*all_env;

	all_env = NULL;
	(void)ac;
	(void)av;
	if (!envp)
		return (0);
	fill_env(envp, &all_env);
	env(&all_env);
	clean_env(&all_env);
	return (0);
}
