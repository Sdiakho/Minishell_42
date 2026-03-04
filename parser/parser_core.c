/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:17:46 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/04 13:48:07 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*build_cmd_node(t_tok **all_tok)
{
	int		cmd_args;
	t_cmd	*cmd;

	printf("%p\n", *all_tok);
	cmd_args = count_arg(*all_tok);
	printf("%p\n", *all_tok);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(&cmd);
	cmd->cmd_param = ft_calloc(sizeof(char *), (cmd_args + 1));
	if (!cmd->cmd_param)
		return (clean_cmd(&cmd), NULL);
	if (!fill_cmd_node(cmd, all_tok))
		return (clean_cmd(&cmd), NULL);
	return (cmd);
}

int	parser(t_tok **all_tok, t_cmd **all_cmd)
{
	t_cmd	*new;

	if (!(*all_tok))
		return (0);
	while (*all_tok)
	{
		new = build_cmd_node(all_tok);
		if (!new)
			return (0);
		add_back_cmd(all_cmd, new);
		if (!(*all_tok))
			break ;
		*all_tok = (*all_tok)->next;
	}
	return (1);
}
