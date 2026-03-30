/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:30:54 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/28 14:39:57 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_exit(t_minishell *mini, int exit_code)
{
	char	*empty_ptr;

	empty_ptr = NULL;
	clean_shell(&empty_ptr, mini);
	exit(exit_code);
}

void	child_process(t_cmd *cmd, t_minishell *mini, int prev_pip, int pip[2])
{
	int	status;

	status = 0;
	if (prev_pip != -1)
	{
		if (dup2(prev_pip, STDIN_FILENO) < 0)
			clean_exit(mini, 1);
		close(prev_pip);
	}
	if (cmd->next)
	{
		if (dup2(pip[1], STDOUT_FILENO) < 0)
			clean_exit(mini, 1);
		close(pip[1]);
		close(pip[0]);
	}
	if (!do_in_redir(cmd))
		clean_exit(mini, 1);
	if (!do_out_redir(cmd))
		clean_exit(mini, 1);
	exec_cmd(cmd, &(mini->all_env), &status, mini);
	clean_exit(mini, status);
}

int	process_loop(t_cmd *tmp, int pip[2], int *prev_pip, t_minishell *mini)
{
	if (tmp->next != NULL)
	{
		if (pipe(pip) < 0)
			return (0);
	}
	tmp->pid = fork();
	if (tmp->pid < 0)
		return (0);
	if (tmp->pid == 0)
		child_process(tmp, mini, *prev_pip, pip);
	if (*prev_pip != -1)
		close(*prev_pip);
	if (tmp->next != NULL)
	{
		close(pip[1]);
		*prev_pip = pip[0];
	}
	return (1);
}
