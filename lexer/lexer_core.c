/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:21:09 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/26 15:51:35 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tok	*lexer(char *line)
{
	int		i;
	t_tok	*all_tok = NULL;
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
			return (clean_tok(&all_tok), NULL);
		if (is_sym(line[i]))
		{
			if (!extract_sym(line, &i, new))
				return (clean_tok(&all_tok), NULL);
		}
		else
			if (!extract_word(line, &i, new))
				return (clean_tok(&all_tok), NULL);
		add_back_tok(&all_tok, new);
	}
	return (all_tok);
}

int main(int ac, char **av)
{
	t_tok *tmp;
	t_tok *test;

	test = lexer(av[1]);
	tmp = test;
	while (tmp)
	{
		printf("Type: %d | Value: [%s]\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	clean_tok(&test);
}

