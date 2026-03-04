/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 10:42:23 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/04 15:03:47 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	process_one(t_tok *old, t_env *all_env)
{
	char	*env_var;
	char	*swap;
	char	*full;

	while (check_env_var(old->value) >= 0)
	{
		env_var = expand_token(old->value);
		if (!env_var)
			return (0);
		swap = get_env_value(env_var, all_env);
		if (!swap)
			return (0);
		full = create_swap(old->value, swap);
		if (!full)
			return (free(swap), 0);
		free(old->value);
		old->value = full;
		free(swap);
	}
	return (1);
}

int	expander(t_tok *all_tok, t_env *all_env)
{
	t_tok	*temp;

	if (!all_tok)
		return (1);
	temp = all_tok;
	while (temp)
	{
		if (temp->type == WORD)
		{
			if (!process_one(temp, all_env))
				return (clean_env(&all_env), clean_tok(&all_tok), 0);
		}
		temp = temp->next;
	}
	return (1);
}
