/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:46:59 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/28 10:51:34 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_cmd(t_cmd **cmd)
{
	(*cmd)->cmd_param = NULL;
	(*cmd)->redirs = NULL;
	(*cmd)->next = NULL;
	(*cmd)->fd_in = -1;
	(*cmd)->fd_out = -1;
}

void	clean_cmd_params(t_cmd **cmd)
{
	int i;

	i = 0;
	if ((*cmd)->cmd_param)
	{
		while ((*cmd)->cmd_param[i])
		{
			free((*cmd)->cmd_param[i]);
			i++;	
		}
	}
}

void	clean_cmd_redirs(t_cmd **cmd)
{
	t_redir	*tmp;
	
	while ((*cmd)->redirs)
	{
		tmp = (*cmd)->redirs;
		free(tmp->file);
		free(tmp);
		(*cmd)->redirs = (*cmd)->redirs->next;
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
		if (tmp->cmd_param)
			clean_cmd_params(&tmp);
		if (tmp->redirs)
			clean_cmd_redirs(&tmp);
		free(tmp);
		if (!(*cmd))
			break ;
		*cmd = (*cmd)->next;		
	}
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

int	count_redir(t_tok *tmp)
{
	int	count;
	int	redir;

	count = 0;
	redir = 0;
	if (!tmp)
		return (count);
	while (tmp && tmp->type != PIPE)
	{
		if (is_redir(tmp->type))
			redir = 1;
		else if (tmp->type == WORD && redir == 1)
		{
			count++;
			redir = 0;	
		}	
		tmp = tmp->next;
	}
	return (count);
}

int		fill_cmd_node(t_cmd *cmd, t_tok **tmp)
{
	int		i;
	int		redir;
	t_redir *new;
	
	i = 0;
	redir = 0;
	while ((*tmp) && (*tmp)->type != PIPE)
	{
		if((*tmp)->type == WORD && redir == 0)
		{
			cmd->cmd_param[i++] = ft_strnndup((*tmp)->value, 0, ft_strlen((*tmp)->value));
			if (!cmd->cmd_param[i - 1])
				return (i);
		}
		else if (is_redir((*tmp)->type))
		{
			new = (t_redir *)malloc(sizeof(t_redir));
			if (!new)
				return (i);
			new->type = (*tmp)->type;
			new->next = NULL;
			redir = 1;	
		}
		else if ((*tmp)->type == WORD && redir == 1)
		{
			new->file = ft_strnndup((*tmp)->value, 0, ft_strlen((*tmp)->value));
			if (!new->file)
				return(i);
			add_back_redir(&(cmd->redirs), new);
			redir = 0;
		}
		(*tmp) = (*tmp)->next;
	}
	cmd->cmd_param[i] = NULL;
	return(0);
}

t_cmd	*build_cmd_node(t_tok **tmp)
{
	int		cmd_args;
	int		cmd_redirs;
	t_cmd	*cmd;

	printf("%p\n", *tmp);
	cmd_args = count_arg(*tmp);
	printf("%p\n", *tmp);
	cmd_redirs = count_redir(*tmp);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(&cmd);
	cmd->cmd_param = (char **)malloc(sizeof(char *) * (cmd_args + 1));
	if (!cmd->cmd_param)
		return (free(cmd), NULL);
	if (fill_cmd_node(cmd, tmp) == 0)
		return (cmd);
	return (NULL);
}

int	cmds(t_tok **tmp, t_cmd **cmd)
{
	t_cmd	*new;

	while (*tmp)
	{
		new = build_cmd_node(tmp);
		if (!new)
			return (0);
		add_back_cmd(cmd, new);
		if (!(*tmp))
			break ;
		*tmp = (*tmp)->next;
	}
	return (1);
}
