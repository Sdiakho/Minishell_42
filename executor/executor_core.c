/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:43:15 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/21 18:10:22 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_pipeline(t_cmd *all_cmd)
{
	t_cmd	*tmp;
	int		status;
	int		final_status;

	tmp = all_cmd;
	final_status = 1;
	while (tmp)
	{
		if (tmp->pid != -1)
		{
			waitpid(tmp->pid, &status, 0);
			if (WIFEXITED(status))
				final_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				final_status = 128 + WTERMSIG(status);
				write(1, "\n", 1);
			}
			else
				final_status = 1;
		}
		tmp = tmp->next;
	}
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
		if (!only_one_blt(mini->all_cmd, &(mini->all_env)))
			return (0);
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
