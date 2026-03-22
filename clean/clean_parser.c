/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:24:12 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/13 17:23:27 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_cmd_params(t_cmd **cmd)
{
	int	i;

	i = 0;
	if ((*cmd)->cmd_param)
	{
		while ((*cmd)->cmd_param[i])
		{
			free((*cmd)->cmd_param[i]);
			i++;
		}
		free((*cmd)->cmd_param);
	}
}

void	clean_cmd_redirs(t_cmd **cmd)
{
	t_redir	*tmp;

	while ((*cmd)->redirs)
	{
		tmp = (*cmd)->redirs;
		(*cmd)->redirs = (*cmd)->redirs->next;
		if (tmp->type == H_DOC)
			unlink(tmp->file);
		free(tmp->file);
		free(tmp);
	}
}

void	clean_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!(*cmd))
		return ;
	while ((*cmd))
	{
		tmp = (*cmd);
		*cmd = (*cmd)->next;
		if (tmp->cmd_param)
			clean_cmd_params(&tmp);
		if (tmp->redirs)
			clean_cmd_redirs(&tmp);
		free(tmp);
	}
}
