/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:15:15 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/25 13:15:05 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*all_env;
	char	*line;

	if (ac != 1)
		return (0);
	(void)av;
	all_env = NULL;
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
		free(line);
	}
	clear_history();
	clean_env(&all_env);
	return (0);
}
