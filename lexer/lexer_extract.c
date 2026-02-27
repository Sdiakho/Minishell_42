/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:47:12 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/27 09:55:22 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sym_great(char *str, int *i, t_tok *new)
{
	if (str[*i + 1] == '>')
	{
		new->type = D_GREAT;
		new->value = ft_strnndup(str, *i, *i + 2);
		*i += 2;
		if (!new->value)
			return (free(new), 0);
		return (1);
	}
	else
	{
		new->type = GREAT;
		new->value = ft_strnndup(str, *i, *i + 1);
		*i += 1;
		if (!new->value)
			return (free(new), 0);
		return (1);
	}
}

int	sym_less(char *str, int *i, t_tok *new)
{
	if (str[*i + 1] == '<')
	{
		new->type = D_LESS;
		new->value = ft_strnndup(str, *i, *i + 2);
		*i += 2;
		if (!new->value)
			return (free(new), 0);
		return (1);
	}
	else
	{
		new->type = LESS;
		new->value = ft_strnndup(str, *i, *i + 1);
		*i += 1;
		if (!new->value)
			return (free(new), 0);
		return (1);
	}
}

int	sym_pipe(char *str, int *i, t_tok *new)
{
	new->type = PIPE;
	new->value = ft_strnndup(str, *i, *i + 1);
	*i += 1;
	if (!new->value)
		return (free(new), 0);
	return (1);
}

int	extract_sym(char *str, int *i, t_tok *new)
{
	if (str[*i] == '>')
		return (sym_great(str, i, new));
	else if (str[*i] == '<')
		return (sym_less(str, i, new));
	else if (str[*i] == '|')
		return (sym_pipe(str, i, new));
	return (0);
}

int	extract_word(char *str, int *i, t_tok *new)
{
	int	in_single;
	int	in_double;
	int	start;

	in_single = 0;
	in_double = 0;
	start = *i;
	while (str[*i])
	{
		if (str[*i] == '\'' && in_double == 0)
			in_single = !in_single;
		else if (str[*i] == '\"' && in_single == 0)
			in_double = !in_double;
		else if ((str[*i] == ' ' || is_sym(str[*i]))
			&& in_single == 0 && in_double == 0)
			break ;
		(*i)++;
	}
	new->type = WORD;
	new->value = ft_strnndup(str, start, *i);
	if (!new->value)
		return (free(new), 0);
	return (1);
}
