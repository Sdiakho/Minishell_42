/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:36:31 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/16 19:34:42 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_loop(char **line, t_minishell *mini)
{
	if (line)
		if (*line)
			free(*line);
	if (mini->all_cmd)
		clean_cmd(&(mini->all_cmd));
	if (mini->all_tok)
		clean_tok(&(mini->all_tok));
	*line = NULL;
	mini->all_cmd = NULL;
	mini->all_tok = NULL;
}

void	clean_shell(char **line, t_minishell *mini)
{
	clean_loop(line, mini);
	if (mini->all_env)
		clean_env(&(mini->all_env));
	clear_history();
}
