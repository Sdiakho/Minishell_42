/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:38:01 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/30 21:18:32 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**env_list_to_array(t_env *all_env)
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

void	exec_extern(t_cmd *cmd, t_env **all_env, t_minishell *mini)
{
	char	*full;
	char	**cur_env;
	int		status;

	cur_env = env_list_to_array(*all_env);
	if (!cur_env)
		error_exit_msg("minishell: split error", 1, mini);
	verif_point(cmd, mini, cur_env);
	full = path(cmd, *all_env, &status);
	if (!full)
	{
		free_split(cur_env);
		ft_putstr_fd(cmd->cmd_param[0], 2);
		if (status == 127)
			error_exit_msg("minishell: command not found", status, mini);
		else if (status == 126)
			error_exit_msg("minishell: permission denied", status, mini);
	}
	verif_dir(full, mini, cur_env);
	execve(full, cmd->cmd_param, cur_env);
	free_split(cur_env);
	free(full);
	error_exit_msg("minishell: Execve error", 126, mini);
}

void	exec_cmd(t_cmd *cmd, t_env **all_env, int *status, t_minishell *mini)
{
	sig_dfl();
	if (is_builtin(cmd->cmd_param[0]))
		*status = exec_builtin(cmd, all_env, mini);
	else
		exec_extern(cmd, all_env, mini);
}
