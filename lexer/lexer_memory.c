/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:48:53 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/27 09:56:29 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tok	*create_node_tok(void)
{
	t_tok	*new;

	new = (t_tok *)malloc(sizeof(t_tok));
	if (!new)
		return (NULL);
	new->type = UNKNOWN;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_back_tok(t_tok **all_tok, t_tok *new)
{
	t_tok	*tmp;

	if (!(*all_tok))
	{
		*all_tok = new;
		return ;
	}
	tmp = *all_tok;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	clean_tok(t_tok **all_tok)
{
	t_tok	*tmp;

	if (!all_tok || !(*all_tok))
		return ;
	while (*all_tok)
	{
		tmp = *all_tok;
		*all_tok = (*all_tok)->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
