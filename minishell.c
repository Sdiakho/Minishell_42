/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:15:15 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/27 11:17:32 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*all_env;
	t_tok	*all_tok;
	t_tok	*tmp;
	char	*line;

	if (ac != 1)
		return (0);
	(void)av;
	all_env = NULL;
	all_tok = NULL;
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
		if (check_syntax(all_tok))
			printf("Valid\n");
		else
			printf("Invalid\n");
		free(line);
		clean_tok(&all_tok);
	}
	clear_history();
	clean_env(&all_env);
	return (0);
}
