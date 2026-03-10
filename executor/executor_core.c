/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:43:15 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/10 13:43:22 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	do_out_redir(t_cmd *cmd)
{
	t_redir *tmp;
	int		fd;

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
		if (tmp->type == LESS)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd < 0)
				return (0);
			if (dup2(fd, STDIN_FILENO) < 0)
				return (0);
			close(fd);
		}
		else if (tmp->type == D_LESS)
		{
			//TODO:here_doc
		}
		tmp = tmp->next;
	}
	return (1);
}

int	exec_builtin(t_cmd *cmd, t_env **env)
{
	// if (!ft_strncmp(cmd->cmd_param[0], "cd", 3))
	// 	return (ft_cd(cmd, env));
	// if (!ft_strncmp(cmd->cmd_param[0], "echo", 5))
	// 	return (ft_echo(cmd));
	// if (!ft_strncmp(cmd->cmd_param[0], "pwd", 4))
	// 	return (ft_pwd(cmd));
	// if (!ft_strncmp(cmd->cmd_param[0], "export", 7))
	// 	return (ft_export(cmd, env));
	// if (!ft_strncmp(cmd->cmd_param[0], "unset", 6))
	// 	return (ft_unset(cmd, env));
	// if (!ft_strncmp(cmd->cmd_param[0], "env", 4))
	// 	return (ft_env(env));
	// if (!ft_strncmp(cmd->cmd_param[0], "exit", 5))
	// 	return (ft_exit(cmd, env));
	if (cmd && *env)
		return (1);
	return (0);
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

int	count_env(t_env *all_env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = all_env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*path_join(t_env *env)
{
	char	*temp;
	char	*all;
	
	if (!env->value)
		return (ft_strnndup(env->name, 0, ft_strlen(env->name)));
	temp = ft_strjoin(env->name, "=");
	if (!temp)
		return (NULL);
	all = ft_strjoin(temp, env->value);
	free(temp);
	if (!all)
		return (NULL);
	return (all);
}

char **env_list_to_array(t_env *all_env)
{
	int		count;
	int		i;
	char	**cur_envp;
	char	*all;
	t_env	*tmp;
	
	count = count_env(all_env);
	cur_envp = ft_calloc(count + 1, sizeof(char *));
	if (!cur_envp)
		return (NULL);
	tmp = all_env;
	i = 0;
	while (tmp)
	{
		all = path_join(tmp);
		if (!all)
			return (free_split(cur_envp), NULL);
		cur_envp[i] = all;
		i++;
		tmp = tmp->next;
	}
	cur_envp[i] = NULL;
	return (cur_envp);
}

void	exec_extern(t_cmd *cmd, t_env **all_env)
{
	char	*full;
	char	**cur_env;
	int		status;

	cur_env	= env_list_to_array(*all_env);
	if (!cur_env)
		error_exit_msg("Split error", 1);
	full = path(cmd, *all_env, &status);
	if (!full)
	{
		free_split(cur_env);
		ft_putstr_fd(cmd->cmd_param[0], 2);
		if (status == 127)
			error_exit_msg(": Command not found", status);
		else if (status == 126)
			error_exit_msg(": Permission denied", status);
	}
	execve(full, cmd->cmd_param, cur_env);
	free_split(cur_env);
	error_exit_msg("Execve error", 126);
} 

void	exec_cmd(t_cmd *cmd, t_env **all_env)
{
	if (is_builtin(cmd->cmd_param[0]))
		exec_builtin(cmd, all_env);
	else
		exec_extern(cmd, all_env);
}

void	child_process(t_cmd *cmd, t_env **all_env, int prev_pip, int pip[2])
{
	if (prev_pip != -1)
	{
		if (dup2(prev_pip, STDIN_FILENO) < 0)
			exit(1);
		close(prev_pip);
	}
	if (cmd->next)
	{
		if (dup2(pip[1], STDOUT_FILENO) < 0)
			exit(1);
		close(pip[1]);
		close(pip[0]);
	}
	if (!do_in_redir(cmd))
		exit(1);
	if (!do_out_redir(cmd))
		exit(1);
	exec_cmd(cmd, all_env);
}

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
			else
				final_status = 1;
		}
		tmp = tmp->next;
	}
	return (final_status);
}

int	loop_pipe_ms(t_cmd *all_cmd, t_env **all_env)
{
	t_cmd	*tmp;
	int		prev_pip;
	int		pip[2];

	tmp = all_cmd;
	prev_pip = -1;
	while (tmp)
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
			child_process(tmp, all_env, prev_pip, pip);
		if (prev_pip != -1)
			close(prev_pip);
		if (tmp->next != NULL)
		{
			close(pip[1]);
			prev_pip = pip[0];
		}
		tmp = tmp->next;
	}
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

int	executor(t_cmd *all_cmd, t_env **all_env, int *status)
{
	int		save_stdin;
	int		save_stdout;

	if (!all_cmd)
		return (0);
	if (all_cmd->cmd_param && all_cmd->cmd_param[0] != NULL)
	{
		if (is_builtin(all_cmd->cmd_param[0]) && !all_cmd->next)
		{
			if (!only_one_blt(all_cmd, all_env))
				return (0);
			return (1);
		}
		else
		{
			if (!loop_pipe_ms(all_cmd, all_env))
				return (0);
			*status = wait_pipeline(all_cmd);
			return (1);
		}
	}
	else
	{
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
}
