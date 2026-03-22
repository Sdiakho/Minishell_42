/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:15:15 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/21 19:05:28 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

t_minishell	*init_shell(char **envp, struct sigaction *sa)
{
	t_minishell	*mini;

	mini = (t_minishell *)malloc(sizeof(t_minishell));
	if (!mini)
		return (NULL);
	mini->all_env = NULL;
	mini->all_cmd = NULL;
	mini->all_tok = NULL;
	mini->exit_status = 0;
	fill_env(envp, &(mini->all_env));
	*sa = sig_init(sig_handler);
	return (mini);
}

char	*process_line(t_minishell *mini)
{
	char	*line;

	line = readline("minishell> ");
	if (g_status != 0)
		mini->exit_status = g_status;
	if (!line)
		return (NULL);
	if (line[0] != '\0' && !ft_strschr(line, "<<"))
		add_history(line);
	return (line);
}

int	build_ast_from_line(char *line, t_minishell *mini)
{
	if (!lexer(line, &(mini->all_tok)))
		return (0);
	if (!expander(mini->all_tok, mini->all_env, &(mini->exit_status)))
		return (0);
	if (!parser(&(mini->all_tok), &(mini->all_cmd)))
		return (0);
	if (!here_docs(mini))
		return (0);
	return (1);
}

int	launch_execution(t_minishell *mini)
{
	if (mini->all_cmd)
	{
		sig_ign();
		if (!executor(mini))
			return (0);
		return (1);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell			*mini;
	char				*line;
	struct sigaction	sa;

	(void)argv;
	(void)argc;
	mini = init_shell(envp, &sa);
	if (!mini)
		return (1);
	while (1)
	{
		sig_main(sa);
		g_status = 0;
		line = process_line(mini);
		if (!line)
			break ;
		if (!build_ast_from_line(line, mini))
		{
			clean_loop(&line, mini);
			continue ;
		}
		launch_execution(mini);
		clean_loop(&line, mini);
	}
	return (clean_shell(&line, mini), 0);
}
