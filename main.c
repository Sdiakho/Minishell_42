//#include "minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	int		i;
// 	t_env	*all_env;
// 	t_tok	*all_tok;
// 	t_cmd	*all_cmd;
// 	t_tok	*tmp;
// 	t_cmd	*tmp2;
// 	t_env	*env_test;
// 	char	*line;

// 	if (ac != 1)
// 		return (0);
// 	(void)av;
// 	all_env = NULL;
// 	all_tok = NULL;
// 	all_cmd = NULL;
// 	if (!envp)
// 		return (1);
// 	if (!fill_env(envp, &all_env))
// 		printf("Attention il n'y a pas de variable d'environnement");
// 	env_test = malloc(sizeof(t_env));
// 	env_test->name = ft_strnndup("TEST", 0, 5);
// 	env_test->value = ft_strnndup("sdiakho", 0, 8);
// 	add_front_env(&all_env, env_test);
// 	// while (all_env)
// 	// {
// 	// 	printf("%s\n", all_env->name);
// 	// 	all_env = all_env->next;
// 	// }
// 	signal(SIGQUIT, SIG_IGN);
// 	while (1)
// 	{
// 		line = readline("minishell>");
// 		if (!line)
// 			break ;
// 		if (line[0] != '\0')
// 			add_history(line);
// 		lexer(line, &all_tok);
// 		tmp = all_tok;
// 		while (tmp)
// 		{
// 			printf("Type: %d | Value: [%s]\n", tmp->type, tmp->value);
// 			tmp = tmp->next;
// 		}
// 		printf("La taille du double tableau d'args sera de %d\n", count_arg(all_tok));
// 		expander(all_tok, all_env);
// 		tmp = all_tok;
// 		while (tmp)
// 		{
// 			printf("Type: %d | Value: [%s]\n", tmp->type, tmp->value);
// 			tmp = tmp->next;
// 		}
// 		parser(&all_tok, &all_cmd);
// 		tmp2 = all_cmd;
// 		while (tmp2)
// 		{
// 			i = 0;
// 			while (tmp2->cmd_param[i])
// 			{
// 				printf("%s\n", tmp2->cmd_param[i]);
// 				i++;	
// 			}
// 			while (tmp2->redirs)
// 			{
// 				printf("avec la redirection %d vers %s\n", tmp2->redirs->type, tmp2->redirs->file);
// 				tmp2->redirs = tmp2->redirs->next;
// 			}
// 			tmp2 = tmp2->next;
// 		}
// 		free(line);
// 		clean_tok(&all_tok);
// 		clean_cmd(&all_cmd);
// 	}
// 	clear_history();
// 	clean_env(&all_env);
// 	return (0);
// }


// int main(int argc, char **argv, char **envp)
// {
// 	t_minishell			*mini;
// 	char				*line;
// 	struct sigaction	sa;

// 	(void)argv;
// 	(void)argc;
// 	mini = (t_minishell *)malloc(sizeof(t_minishell));
// 	if (!mini)
// 		return (1);
// 	init_mini(&mini);
// 	fill_env(envp, &(mini->all_env));
// 	sa = sig_init(sig_handler);
// 	while (1)
// 	{
// 		sig_main(sa);
// 		g_status = 0;
// 		line = process_line(mini);
// 		if (!line)
// 			break ;
// 		if (!build_ast_from_line(line, mini))
// 			clean_loop(&line, mini);
// 		launch_execution(mini);
// 		clean_loop(&line, mini);
// 	}
// 	return (clean_shell(&line, mini), 0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char    *line;
//     t_cmd   *all_cmd;
//     t_env   *all_env;
// 	t_tok	*all_tok;
//     int     exit_status;
//     all_cmd = NULL;
//     all_env = NULL;
//     all_tok = NULL;
//     (void)argc;
//     (void)argv;
//     exit_status = 0;
//     // 1. Initialisation de ton environnement (transformer envp en t_env)
//     // all_env = init_env(envp);
// 	fill_env(envp, &all_env);
//     struct sigaction    sa;
//     sa = sig_init(sig_handler);
//     while (1)
//     {
//         sigaction(SIGINT, &sa, NULL);
//         signal(SIGQUIT, SIG_IGN);
//         g_status = 0;
//         // 2. Récupération de la ligne
//         line = readline("minishell> ");
//         if (g_status != 0)
//             exit_status = g_status;
//         if (!line) // Si l'utilisateur fait Ctrl+D (EOF)
//             break ;
        
//         if (line[0] != '\0' && !ft_strschr(line, "<<"))
//             add_history(line);

//         // 3. Parsing (tu remplaces ça par tes vraies fonctions)
//         // all_cmd = parse_line(line, all_env);
// 		lexer(line, &all_tok);
// 		expander(all_tok, all_env, &exit_status);
// 		parser(&all_tok, &all_cmd);
//         if (!here_docs(&all_cmd, &exit_status))
//             clean_cmd(&all_cmd);
//         sig_ign();
//         // 4. L'Exécution Nucléaire
//         if (all_cmd)
//             executor(all_cmd, &all_env, &exit_status);
//         // 5. Le Nettoyage de la RAM (Étape CRITIQUE pour Valgrind)
//         // free(line);
//         // free_cmd_list(all_cmd); // Ta fonction qui détruit proprement l'arbre syntaxique
// 		free(line);
// 		clean_tok(&all_tok);
// 		clean_cmd(&all_cmd);
//     }
// 	clean_env(&all_env);
// 	clear_history();
//     // 6. Le Nettoyage Final (après le break du Ctrl+D)
//     // free_env_list(all_env);
//     // clear_history();
    
//     return (exit_status);
// }

// char	*create_here_doc(int *i)
// {
// 	char	*here_doc;
// 	char	*nb;

// 	nb = ft_itoa(*i);
// 	if (!nb)
// 		return (NULL);
// 	here_doc = ft_strjoin(".temp_heredoc_", nb);
// 	free(nb);
// 	if (!here_doc)
// 		return (NULL);
// 	(*i)++;
// 	return (here_doc);
// }
// void	replace_here_doc(char *file_name, t_redir *redir)
// {
// 	redir->type = H_DOC;
// 	if (redir->file)
// 		free(redir->file);
// 	redir->file = file_name;
// }

// // int	process_here_doc(t_redir *redir, int *i, int *exit_status)
// // {
// // 	char	*here_doc;
// // 	char	*line;
// // 	int		fd_temp;
// // 	int		lim_len;
// // 	int		pid;
// // 	int		status;

// // 	here_doc = create_here_doc(i);
// // 	if (!here_doc)
// // 		return (-1);
// // 	sig_ign();
// // 	pid = fork();
// // 	if (pid < 0)
// // 		return (free(here_doc), -1);
// // 	if (pid == 0)
// // 	{
// // 		signal(SIGINT, SIG_DFL);
// // 		fd_temp = open(here_doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// // 		free(here_doc);
// // 		if (fd_temp < 0)
// // 			exit(1);
// // 		lim_len = ft_strlen(redir->file);
// // 		while (1)
// // 		{
// // 			write(2, "heredoc> ", 9);
// // 			line = get_next_line(STDIN_FILENO);
// // 			if (!line)
// // 				break ;
// // 			if (ft_strncmp(line, redir->file, lim_len) == 0 && line[lim_len] == '\n')
// // 			{
// // 				free(line);
// // 				break ;
// // 			}
// // 			write(fd_temp, line, ft_strlen(line));
// // 			free(line);
// // 		}
// // 		close(fd_temp);
// // 		exit(0);
// // 	}
// // 	waitpid(pid, &status, 0);
// // 	replace_here_doc(here_doc, redir);
// // 	if (WIFSIGNALED(status))
// // 	{
// // 		write(2, "\n", 1);
// // 		*exit_status = 128 + WTERMSIG(status);
// // 		return (-1);
// // 	}
// // 	else
// // 	{
// // 		*exit_status = WEXITSTATUS(status);
// // 		return (0);
// // 	}
// // }

// int	process_exit_code(int status, int *exit_status)
// {
// 	if (WIFSIGNALED(status))
// 	{
// 		write(2, "\n", 1);
// 		*exit_status = 128 + WTERMSIG(status);
// 		return (-1);
// 	}
// 	else
// 	{
// 		*exit_status = WEXITSTATUS(status);
// 		return (0);
// 	}
// }

// void	run_child_heredoc(char *here_doc, t_redir *redir)
// {
// 	int		fd_temp;
// 	int		lim_len;
// 	char	*line;

// 	fd_temp = open(here_doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	free(here_doc);
// 	if (fd_temp < 0)
// 		exit(1);
// 	lim_len = ft_strlen(redir->file);
// 	while (1)
// 	{
// 		write(2, "heredoc> ", 9);
// 		line = get_next_line(STDIN_FILENO);
// 		if (!line)
// 			break ;
// 		if (ft_strncmp(line, redir->file, lim_len) == 0 && line[lim_len] == '\n')
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd_temp, line, ft_strlen(line));
// 		free(line);
// 	}
// 	close(fd_temp);
// 	exit(0);
// }

// int	process_here_doc(t_redir *redir, int *i, int *exit_status)
// {
// 	char	*here_doc;
// 	int		pid;
// 	int		status;

// 	here_doc = create_here_doc(i);
// 	if (!here_doc)
// 		return (-1);
// 	sig_ign();
// 	pid = fork();
// 	if (pid < 0)
// 		return (free(here_doc), -1);
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		run_child_heredoc(here_doc, redir);
// 	}
// 	waitpid(pid, &status, 0);
// 	replace_here_doc(here_doc, redir);
// 	return (process_exit_code(status, exit_status));
// }

// int here_docs(t_cmd **all_cmd, int *exit_status)
// {
// 	t_cmd	*tmp;
// 	t_redir	*temp;
// 	int		i;

// 	tmp = *all_cmd;
// 	i = 1;
// 	while (tmp)
// 	{
// 		temp = tmp->redirs;
// 		while (temp)
// 		{
// 			if (temp->type == D_LESS)
// 				if (process_here_doc(temp, &i, exit_status) != 0)
// 					return (0);
// 			temp = temp->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }
