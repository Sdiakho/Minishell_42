/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:43:15 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/30 21:51:45 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop_wait(t_cmd *all_cmd, int *f_status)
{
	t_cmd	*tmp;
	int		status;
	int		is_printed;

	is_printed = 0;
	tmp = all_cmd;
	while (tmp)
	{
		if (tmp->pid != -1)
		{
			waitpid(tmp->pid, &status, 0);
			if (WIFEXITED(status))
				*f_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				*f_status = 128 + WTERMSIG(status);
				if (is_printed == 0 && (*f_status == 130 || *f_status == 131))
					write(1, "\n", 1);
				is_printed++;
			}
			else
				*f_status = 1;
		}
		tmp = tmp->next;
	}
}

int	wait_pipeline(t_cmd *all_cmd)
{
	int		final_status;

	final_status = 1;
	loop_wait(all_cmd, &final_status);
	return (final_status);
}

int	loop_pipe_ms(t_minishell *mini)
{
	t_cmd	*tmp;
	int		prev_pip;
	int		pip[2];

	tmp = mini->all_cmd;
	prev_pip = -1;
	while (tmp)
	{
		if (!process_loop(tmp, pip, &prev_pip, mini))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	process_cmd(t_minishell *mini)
{
	if (is_builtin(mini->all_cmd->cmd_param[0]) && !mini->all_cmd->next)
	{
		if (!only_one_blt(mini))
		{
			mini->exit_status = 1;
			return (0);
		}
		return (1);
	}
	else
	{
		if (!loop_pipe_ms(mini))
			return (0);
		mini->exit_status = wait_pipeline(mini->all_cmd);
		return (1);
	}
}

int	executor(t_minishell *mini)
{
	if (!mini->all_cmd)
		return (0);
	if (mini->all_cmd->cmd_param && mini->all_cmd->cmd_param[0] != NULL)
	{
		if (!process_cmd(mini))
			return (0);
		return (1);
	}
	else
	{
		if (!process_just_redir(mini->all_cmd))
			return (0);
		return (1);
	}
}
