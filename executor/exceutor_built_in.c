/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceutor_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:36:59 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/21 19:31:50 by sdiakho          ###   ########.fr       */
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
	if (!ft_strncmp(cmd->cmd_param[0], "env", 4))
	 	return (ft_env(env));
	// if (!ft_strncmp(cmd->cmd_param[0], "exit", 5))
	// 	return (ft_exit(cmd, env));
	if (cmd && *env)
		return (1);
	return (0);
}
