/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:22:30 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/10 13:54:10 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_cmd(t_cmd **cmd)
{
	(*cmd)->cmd_param = NULL;
	(*cmd)->redirs = NULL;
	(*cmd)->next = NULL;
	(*cmd)->pid = -1;
}

void	add_back_redir(t_redir **head_redir, t_redir *new)
{
	t_redir	*tmp;

	if (!head_redir)
		return ;
	if (!(*head_redir))
	{
		*head_redir = new;
		return ;
	}
	tmp = *head_redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_back_cmd(t_cmd **head_cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (!head_cmd)
		return ;
	if (!(*head_cmd))
	{
		*head_cmd = new;
		return ;
	}
	tmp = *head_cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
