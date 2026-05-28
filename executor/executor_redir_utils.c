/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:02:04 by sdiakho           #+#    #+#             */
/*   Updated: 2026/05/14 17:06:30 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_out_file(char *file, t_token_type type)
{
	if (type == GREAT)
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

int	open_in_file(char *file)
{
	return (open(file, O_RDONLY));
}
