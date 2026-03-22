/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:33:54 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/21 18:04:59 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_out_redir(t_cmd *cmd)
{
	t_redir		*tmp;
	int			fd;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == GREAT || tmp->type == D_GREAT)
		{
			if (tmp->type == GREAT)
				fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (0);
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (0);
			close(fd);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	do_in_redir(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == LESS || tmp->type == H_DOC)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd < 0)
				return (0);
			if (dup2(fd, STDIN_FILENO) < 0)
				return (0);
			close(fd);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	reset_save(int save_stdin, int save_stdout)
{
	if (dup2(save_stdin, STDIN_FILENO) < 0)
		return (0);
	if (dup2(save_stdout, STDOUT_FILENO) < 0)
		return (0);
	close(save_stdin);
	close(save_stdout);
	return (1);
}

int	only_one_blt(t_cmd *cmd, t_env **all_env)
{
	int		save_stdin;
	int		save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (!do_in_redir(cmd))
	{
		reset_save(save_stdin, save_stdout);
		return (0);
	}
	if (!do_out_redir(cmd))
	{
		reset_save(save_stdin, save_stdout);
		return (0);
	}
	exec_builtin(cmd, all_env);
	if (!reset_save(save_stdin, save_stdout))
		return (0);
	return (1);
}

int	process_just_redir(t_cmd *all_cmd)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (!do_in_redir(all_cmd))
	{
		reset_save(save_stdin, save_stdout);
		return (0);
	}
	if (!do_out_redir(all_cmd))
	{
		reset_save(save_stdin, save_stdout);
		return (0);
	}
	reset_save(save_stdin, save_stdout);
	return (1);
}
