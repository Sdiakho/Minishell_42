/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:35:31 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/30 16:36:33 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_exit_sys(char *msg, int status)
{
	if (msg)
		perror(msg);
	exit(status);
}

void	error_exit_msg(char *msg, int status, t_minishell *mini)
{
	char	*empty_ptr;

	empty_ptr = NULL;
	clean_shell(&empty_ptr, mini);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(status);
}
