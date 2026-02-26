/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:47:41 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/26 15:51:08 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_sym(char c)
{
	char	*sym;
	int		i;

	sym = "<|>";
	i = 0;
	while (sym[i])
	{
		if (sym[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
