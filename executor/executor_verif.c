/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_verif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:01:20 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/30 21:27:02 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	verif_point(t_cmd *cmd, t_minishell *mini, char **cur_env)
{
	if (cmd->cmd_param[0][0] == '.' && cmd->cmd_param[0][1] == '\0')
	{
		free_split(cur_env);
		error_exit_msg("minishell: .: filename argument required", 2, mini);
	}
	if (cmd->cmd_param[0][0] == '.' && cmd->cmd_param[0][1] == '.'
		&& cmd->cmd_param[0][2] == '\0')
	{
		free_split(cur_env);
		error_exit_msg("minishell: ..: command not found", 127, mini);
	}
}

void	verif_dir(char *full_path, t_minishell *mini, char **cur_env)
{
	struct stat	path_stat;

	if (stat(full_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(full_path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		free(full_path);
		free_split(cur_env);
		error_exit_msg(NULL, 126, mini);
	}
}
