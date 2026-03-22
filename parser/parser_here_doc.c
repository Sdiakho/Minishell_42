/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:57:20 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/21 18:00:50 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_exit_code(int status, int *exit_status)
{
	if (WIFSIGNALED(status))
	{
		write(2, "\n", 1);
		*exit_status = 128 + WTERMSIG(status);
		return (-1);
	}
	else
	{
		*exit_status = WEXITSTATUS(status);
		return (0);
	}
}

void	read_heredoc_loop(t_redir *redir, int lim_len, int fd_temp)
{
	char	*line;

	while (1)
	{
		write(2, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, redir->file, lim_len) == 0)
		{
			if (line[lim_len] == '\n')
			{
				free(line);
				break ;
			}
		}
		write(fd_temp, line, ft_strlen(line));
		free(line);
	}
}

void	run_child_heredoc(char *here_doc, t_redir *redir, t_minishell *mini)
{
	int		fd_temp;
	int		lim_len;
	char	*empty_ptr;

	empty_ptr = NULL;
	fd_temp = open(here_doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(here_doc);
	if (fd_temp < 0)
	{
		clean_shell(&empty_ptr, mini);
		exit(1);
	}
	lim_len = ft_strlen(redir->file);
	read_heredoc_loop(redir, lim_len, fd_temp);
	close(fd_temp);
	clean_shell(&empty_ptr, mini);
	exit(0);
}

int	process_here_doc(t_redir *redir, int *i, t_minishell *mini)
{
	char	*here_doc;
	int		pid;
	int		status;

	here_doc = create_here_doc(i);
	if (!here_doc)
		return (-1);
	sig_ign();
	pid = fork();
	if (pid < 0)
		return (free(here_doc), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		run_child_heredoc(here_doc, redir, mini);
	}
	waitpid(pid, &status, 0);
	replace_here_doc(here_doc, redir);
	return (process_exit_code(status, &(mini->exit_status)));
}

int	here_docs(t_minishell *mini)
{
	t_cmd	*tmp;
	t_redir	*temp;
	int		i;

	tmp = mini->all_cmd;
	i = 1;
	while (tmp)
	{
		temp = tmp->redirs;
		while (temp)
		{
			if (temp->type == D_LESS)
				if (process_here_doc(temp, &i, mini) != 0)
					return (0);
			temp = temp->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
