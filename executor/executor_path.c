/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 15:16:58 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/21 18:07:38 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_abs_path(char *path)
{
	if (!path)
		return (0);
	if (ft_strchr(path, '/'))
		return (1);
	return (0);
}

int	test_path(char *path, int *status)
{
	if (access(path, F_OK) < 0)
		return (*status = 127, 0);
	if (access(path, X_OK) < 0)
		return (*status = 126, 0);
	return (1);
}

char	**get_env_path(t_env *all_env)
{
	char	*paths;
	char	**sep_paths;

	if (!all_env)
		return (NULL);
	paths = get_env_value(ft_strnndup("PATH", 0, 4), all_env);
	if (!paths)
		return (NULL);
	sep_paths = ft_split(paths, ":");
	free(paths);
	if (!sep_paths)
		return (NULL);
	return (sep_paths);
}

char	*get_cmd_path(t_cmd *cmd, char **paths, int *status)
{
	int		i;
	char	*temp;
	char	*full;

	if (!cmd || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full = ft_strjoin(temp, cmd->cmd_param[0]);
		free(temp);
		if (!full)
			return (NULL);
		if (test_path(full, status))
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*path(t_cmd *cmd, t_env *all_env, int *status)
{
	char	**env;
	char	*full_path;

	if (!cmd)
		return (NULL);
	*status = 127;
	if (is_abs_path(cmd->cmd_param[0]))
	{
		if (test_path(cmd->cmd_param[0], status))
			return (ft_strnndup(cmd->cmd_param[0], 0,
					ft_strlen(cmd->cmd_param[0])));
		return (NULL);
	}
	else
	{
		env = get_env_path(all_env);
		full_path = get_cmd_path(cmd, env, status);
		if (env)
			free_split(env);
		return (full_path);
	}
}
