/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 11:34:09 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/28 14:52:22 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_home(t_env *all_env)
{
	t_env	*tmp;
	char	*dup_path;

	tmp = all_env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "HOME", 5) == 0)
		{
			if (!tmp->value)
				return (NULL);
			dup_path = ft_strnndup(tmp->value, 0, ft_strlen(tmp->value));
			if (!dup_path)
				return (NULL);
			return (dup_path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	update_path(char *prefix, char *path, t_env **all_env)
{
	t_cmd	*fake_cmd;
	char	*full_var;

	full_var = ft_strjoin(prefix, path);
	if (!full_var)
		return (0);
	fake_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!fake_cmd)
		return (free(full_var), 0);
	fake_cmd->cmd_param = (char **)malloc(sizeof(char *) * 3);
	if (!fake_cmd->cmd_param)
		return (free(full_var), free(fake_cmd), 0);
	fake_cmd->cmd_param[0] = "export";
	fake_cmd->cmd_param[1] = full_var;
	fake_cmd->cmd_param[2] = NULL;
	ft_export(fake_cmd, all_env);
	free(fake_cmd->cmd_param[1]);
	free(fake_cmd->cmd_param);
	free(fake_cmd);
	return (1);
}

int	clret(char *home, int status, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (home)
		free(home);
	return (status);
}

int	process_chdir(char *path)
{
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

int	ft_cd(t_cmd *cmd, t_env **all_env)
{
	int		flag;
	char	*home;
	char	buffer[1024];

	home = extract_home(*all_env);
	if (cmd->cmd_param[1] == NULL)
		if (!home)
			return (ft_putstr_fd("minishell: cd: Home is not set\n", 2), 1);
	if (getcwd(buffer, 1024) == NULL)
		return (clret(home, 1, "Cannot get current working directory path\n"));
	if (cmd->cmd_param[1] == NULL)
		flag = process_chdir(home);
	else
		flag = process_chdir(cmd->cmd_param[1]);
	if (!flag)
		return (clret(home, 1, NULL));
	if (!update_path("OLDPWD=", buffer, all_env))
		return (clret(home, 1, NULL));
	if (getcwd(buffer, 1024) == NULL)
		return (clret(home, 1, "Cannot get current working directory path\n"));
	if (!update_path("PWD=", buffer, all_env))
		return (clret(home, 1, NULL));
	return (clret(home, 0, NULL));
}
