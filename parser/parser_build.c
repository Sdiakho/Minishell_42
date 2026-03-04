/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:20:59 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/04 15:01:57 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_arg(t_tok *tmp)
{
	int	count;
	int	redir;

	count = 0;
	redir = 0;
	if (!tmp)
		return (count);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && redir == 0)
			count++;
		else if (is_redir(tmp->type))
			redir = 1;
		else if (tmp->type == WORD && redir == 1)
			redir = 0;
		tmp = tmp->next;
	}
	return (count);
}

static int	add_argument(t_cmd *cmd, t_tok *token, int *i)
{
	int	len;

	len = ft_strlen(token->value);
	cmd->cmd_param[(*i)++] = ft_strnndup(token->value, 0, len);
	if (!cmd->cmd_param[(*i) - 1])
		return (0);
	return (1);
}

static int	build_redirection(t_cmd *cmd, t_tok **all_tok)
{
	t_redir	*new;
	int		len;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->type = (*all_tok)->type;
	new->next = NULL;
	(*all_tok) = (*all_tok)->next;
	if (!(*all_tok) || (*all_tok)->type != WORD)
		return (free(new), 0);
	len = ft_strlen((*all_tok)->value);
	new->file = ft_strnndup((*all_tok)->value, 0, len);
	if (!new->file)
		return (free(new), 0);
	add_back_redir(&(cmd->redirs), new);
	return (1);
}

int	fill_cmd_node(t_cmd *cmd, t_tok **all_tok)
{
	int	i;

	i = 0;
	while ((*all_tok) && (*all_tok)->type != PIPE)
	{
		if ((*all_tok)->type == WORD)
		{
			if (!add_argument(cmd, (*all_tok), &i))
				return (0);
		}
		else
		{
			if (!build_redirection(cmd, all_tok))
				return (0);
		}
		(*all_tok) = (*all_tok)->next;
	}
	cmd->cmd_param[i] = NULL;
	return (1);
}
