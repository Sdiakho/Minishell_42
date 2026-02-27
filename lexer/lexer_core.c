/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:21:09 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/27 10:02:37 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(char *line, t_tok **all_tok)
{
	int		i;
	t_tok	*new;

	i = 0;
	while (line[i])
	{
		while (line[i] && is_space(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		new = create_node_tok();
		if (!new)
			return (clean_tok(all_tok));
		if (is_sym(line[i]))
		{
			if (!extract_sym(line, &i, new))
				return (clean_tok(all_tok));
		}
		else
			if (!extract_word(line, &i, new))
				return (clean_tok(all_tok));
		add_back_tok(all_tok, new);
	}
}
