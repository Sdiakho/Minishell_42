/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:31:16 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/10 13:41:07 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
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
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**cmd_param;
	t_redir			*redirs;
	pid_t			pid;
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
int		search_key(char *str);
int		ft_env(t_env **all_env);
int		alloc_name(t_env **env, char *str);
int		fill_env(char **envp, t_env **all_env);
int		alloc_env(t_env **env, char *str, int sep);

/** Env_utils  **/
t_env	*create_node_env(void);
void	add_front_env(t_env	**head, t_env *new);

/*  Lexer  */
int		lexer(char *line, t_tok **all_tok);
int		extract_sym(char *str, int *i, t_tok *new);
int		extract_word(char *str, int *i, t_tok *new);

/*  Lexer_utilis  */
int		is_sym(char c);
int		is_space(char c);
t_tok	*create_node_tok(void);
void	add_back_tok(t_tok **all_tok, t_tok *new);

/*  Expander  */
int		expander(t_tok *all_tok, t_env *all_env);

/* Expander_utils */
int		is_alnum(char c);
int		get_var_len(char *str);
int		check_env_var(char *str);
char	*expand_token(char *str);
char	*create_swap(char *str, char *swap);
char	*get_env_value(char *key, t_env *all_env);

/*  Parser  */
int		parser(t_tok **tmp, t_cmd **cmd);
int		fill_cmd_node(t_cmd *cmd, t_tok **all_tok);

/*  Parser_utils  */
void	init_cmd(t_cmd **cmd);
int		count_arg(t_tok *tmp);
int		is_redir(t_token_type type);
int		check_syntax(t_tok *all_tok);
void	add_back_cmd(t_cmd **head_cmd, t_cmd *new);
void	add_back_redir(t_redir **head_redir, t_redir *new);

/*  Executor  */
int	executor(t_cmd *all_cmd, t_env **all_env, int *status);

/*  Executor_utils  */
char	*path(t_cmd *cmd, t_env *all_env, int *status);

/*  Clean  */
void	clean_cmd(t_cmd **cmd);
void	clean_env(t_env **all_env);
void	clean_tok(t_tok **all_tok);

/*  Error  */
void	error_exit_msg(char *msg, int status);

/*  Utils  */
void	free_split(char **words);
int		ft_strlen(const char *str);
int		ft_strchr(char *str, char c);
void	ft_putstr_fd(char *s, int fd);
int		ft_strschr(char *str, char *chr);
char	**ft_split(char *str, char *sep);
int		ft_strncmp(char *s1, char *s2, int n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strnndup(char *src, int start, int end);
char	*ft_strlcopy(char *dst, const char *src, int size);

#endif