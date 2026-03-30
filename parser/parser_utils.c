/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:44:19 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/30 21:29:03 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_parser_error(t_tok *err)
{
	if (!err)
		printf("minishell: parse error unexpected token\n");
	else
		printf("minishell: parse error near '%s'\n", err->value);
}

int	is_redir(t_token_type type)
{
	if (type == GREAT || type == D_GREAT || type == LESS || type == D_LESS)
		return (1);
	return (0);
}

int	check_syntax(t_tok *all_tok)
{
	t_tok	*tmp;

	if (!all_tok)
		return (1);
	tmp = all_tok;
	if (tmp->type == PIPE)
		return (print_parser_error(tmp), 0);
	while (tmp)
	{
		if (tmp->type == UNKNOWN)
			return (print_parser_error(tmp), 0);
		if (is_redir(tmp->type))
		{
			if (!tmp->next || tmp->next->type != WORD)
				return (print_parser_error(tmp->next), 0);
		}
		if (tmp->type == PIPE && tmp->next == NULL)
			return (print_parser_error(tmp->next), 0);
		if (tmp->type == PIPE && tmp->next->type == PIPE)
			return (print_parser_error(tmp->next), 0);
		tmp = tmp->next;
	}
	return (1);
}

int	check_unclosed_quotes(char *line)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_double = 0;
	in_single = 0;
	while (line[i])
	{
		if (line[i] == '\'' && in_double == 0)
			in_single = !in_single;
		else if (line[i] == '\"' && in_single == 0)
			in_double = !in_double;
		i++;
	}
	if (in_double == 0 && in_single == 0)
		return (1);
	return (0);
}
