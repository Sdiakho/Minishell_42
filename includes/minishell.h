/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:31:16 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/27 12:53:21 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_token_type
{
	UNKNOWN,
	WORD,
	PIPE,
	GREAT,
	LESS,
	D_GREAT,
	D_LESS
}	t_token_type;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**cmd_param;
	t_redir			*redirs;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_tok
{
	t_token_type	type;
	char			*value;
	struct s_tok	*next;
}					t_tok;

/*  Env  */
void	env(t_env **all_env);
int		search_key(char *str);
void	alloc_name(t_env **env, char *str);
t_env	*fill_env(char **envp, t_env **all_env);
void	alloc_env(t_env **env, char *str, int sep);

/** Env_utils  **/
t_env	*create_node_env(void);
void	add_front_env(t_env	**head, t_env *new);

/*  Lexer  */
void	lexer(char *line, t_tok **all_tok);
int		extract_sym(char *str, int *i, t_tok *new);
int		extract_word(char *str, int *i, t_tok *new);

/*  Lexer_utilis  */
int		is_sym(char c);
int		is_space(char c);
t_tok	*create_node_tok(void);
void	add_back_tok(t_tok **all_tok, t_tok *new);

/*  Parser  */

/*  Parser_utils  */
int		check_syntax(t_tok *all_tok);

/*  Clean  */
void	clean_env(t_env **all_env);
void	clean_tok(t_tok **all_tok);

/*  Utils  */
int		ft_strlen(const char *str);
char	*ft_strnndup(char *src, int start, int end);

#endif