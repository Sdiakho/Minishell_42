#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char    *line;
    t_cmd   *all_cmd;
    t_env   *all_env;
	t_tok	*all_tok;
    int     status;

    all_cmd = NULL;
    all_env = NULL;
    all_tok = NULL;
    (void)argc;
    (void)argv;
    status = 0;
    
    // 1. Initialisation de ton environnement (transformer envp en t_env)
    // all_env = init_env(envp);
	signal(SIGQUIT, SIG_IGN);
	fill_env(envp, &all_env);
    while (1)
    {
        // 2. Récupération de la ligne
        line = readline("minishell> ");
        if (!line) // Si l'utilisateur fait Ctrl+D (EOF)
            break ;
        
        if (line[0] != '\0' && !ft_strschr(line, ">>"))
            add_history(line);

        // 3. Parsing (tu remplaces ça par tes vraies fonctions)
        // all_cmd = parse_line(line, all_env);
		lexer(line, &all_tok);
		expander(all_tok, all_env);
		parser(&all_tok, &all_cmd);
        // 4. L'Exécution Nucléaire
        if (all_cmd)
            executor(all_cmd, &all_env, &status);

        // 5. Le Nettoyage de la RAM (Étape CRITIQUE pour Valgrind)
        // free(line);
        // free_cmd_list(all_cmd); // Ta fonction qui détruit proprement l'arbre syntaxique
		free(line);
		clean_tok(&all_tok);
		clean_cmd(&all_cmd);
    }
    
	clean_env(&all_env);
	clear_history();
    // 6. Le Nettoyage Final (après le break du Ctrl+D)
    // free_env_list(all_env);
    // clear_history();
    
    return (status);
}