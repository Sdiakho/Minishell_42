/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:22:24 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/14 13:59:43 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_env_var(char *str)
{
	int	i;
	int	in_double;
	int	in_single;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '$' && in_single == 0)
			return (i);
		else if (str[i] == '\'' && in_double == 0)
			in_single = !in_single;
		else if (str[i] == '\"' && in_single == 0)
			in_double = !in_double;
		i++;
	}
	return (-1);
}

int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (-1);
	if (str[i] == '?')
		return (1);
	while (str[i])
	{
		if (str[i] != '_' && !is_alnum(str[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*expand_token(char *str)
{
	int		pos_dl;
	int		len_var;
	char	*exp_var;

	pos_dl = check_env_var(str);
	if (pos_dl == -1)
		return (NULL);
	else
	{
		len_var = get_var_len(str + pos_dl + 1);
		if (len_var == -1 || len_var == 0)
			return (NULL);
		if (len_var == 1)
		{
			if (str[pos_dl + 1] == '?')
				return ("?");
		}
		exp_var = ft_strnndup(str + pos_dl + 1, 0, len_var);
		if (!exp_var)
			return (NULL);
		return (exp_var);
	}
}
