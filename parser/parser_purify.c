/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_purify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:57:39 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/30 21:29:30 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_purify(char *param, int *count_single, int *count_double)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (param[i])
	{
		if (param[i] == '\'' && in_double == 0)
		{
			in_single = !in_single;
			(*count_single)++;
		}
		else if (param[i] == '\"' && in_single == 0)
		{
			in_double = !in_double;
			(*count_double)++;
		}
		i++;
	}
	return (1);
}

void	purify_copy(char *pure, char *param, int in_single, int in_double)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (param[i])
	{
		if (param[i] == '\'' && in_double == 0)
		{
			in_single = !in_single;
			i++;
		}
		else if (param[i] == '\"' && in_single == 0)
		{
			in_double = !in_double;
			i++;
		}
		else
		{
			pure[j] = param[i];
			i++;
			j++;
		}
	}
	pure[j] = '\0';
}

int	update_purify(char **param, int count_single, int count_double, int i)
{
	int		len;
	int		in_single;
	int		in_double;
	char	*pure;

	len = ft_strlen(param[i]) - (count_double + count_single);
	in_single = 0;
	in_double = 0;
	pure = (char *)malloc(len + 1);
	if (!pure)
		return (0);
	if (len == 0)
		pure[0] = '\0';
	else
		purify_copy(pure, param[i], in_single, in_double);
	free(param[i]);
	param[i] = pure;
	return (1);
}

int	purify_cmd(t_cmd *all_cmd)
{
	t_cmd	*tmp;
	int		i;
	int		count_single;
	int		count_double;

	if (!all_cmd)
		return (1);
	tmp = all_cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_param[i])
		{
			count_single = 0;
			count_double = 0;
			process_purify(tmp->cmd_param[i], &count_single, &count_double);
			update_purify(tmp->cmd_param, count_single, count_double, i);
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}
