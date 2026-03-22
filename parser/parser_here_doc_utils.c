/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_doc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:20:33 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/21 18:02:44 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_here_doc(int *i)
{
	char	*here_doc;
	char	*nb;

	nb = ft_itoa(*i);
	if (!nb)
		return (NULL);
	here_doc = ft_strjoin(".temp_heredoc_", nb);
	free(nb);
	if (!here_doc)
		return (NULL);
	(*i)++;
	return (here_doc);
}

void	replace_here_doc(char *file_name, t_redir *redir)
{
	redir->type = H_DOC;
	if (redir->file)
		free(redir->file);
	redir->file = file_name;
}
