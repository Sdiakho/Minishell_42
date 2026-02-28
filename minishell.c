/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:15:15 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/28 10:43:55 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_env	*all_env;
	t_tok	*all_tok;
	t_cmd	*all_cmd;
	t_tok	*tmp;
	t_cmd	*tmp2;
	char	*line;

	if (ac != 1)
		return (0);
	(void)av;
	all_env = NULL;
	all_tok = NULL;
	all_cmd = NULL;
	if (!envp)
		return (1);
	fill_env(envp, &all_env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell>");
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		lexer(line, &all_tok);
		tmp = all_tok;
		while (tmp)
		{
			printf("Type: %d | Value: [%s]\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
		printf("La taille du double tableau d'args sera de %d\n", count_arg(all_tok));
		printf("La nombre de noeud de redir sera de %d\n", count_redir(all_tok));
		cmds(&all_tok, &all_cmd);
		tmp2 = all_cmd;
		while (tmp2)
		{
			i = 0;
			while (tmp2->cmd_param[i])
			{
				printf("%s\n", tmp2->cmd_param[i]);
				i++;	
			}
			while (tmp2->redirs)
			{
				printf("avec la redirection %d vers %s\n", tmp2->redirs->type, tmp2->redirs->file);
				tmp2->redirs = tmp2->redirs->next;
			}
			tmp2 = tmp2->next;
		}
		free(line);
		clean_tok(&all_tok);
		clean_cmd(&all_cmd);
	}
	clear_history();
	clean_env(&all_env);
	return (0);
}
