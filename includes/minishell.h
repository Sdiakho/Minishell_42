/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:31:16 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/21 18:49:23 by sdiakho          ###   ########.fr       */
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
	D_LESS,
	H_DOC
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

typedef struct sigaction	t_sig;

typedef struct s_minishell
{
	t_env	*all_env;
	t_tok	*all_tok;
	t_cmd	*all_cmd;
	int		exit_status;
}			t_minishell;

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
int		expander(t_tok *all_tok, t_env *all_env, int *exit_status);

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
int		here_docs(t_minishell *mini);

/*  Parser_utils  */
void	init_cmd(t_cmd **cmd);
int		count_arg(t_tok *tmp);
char	*create_here_doc(int *i);
int		is_redir(t_token_type type);
int		check_syntax(t_tok *all_tok);
void	add_back_cmd(t_cmd **head_cmd, t_cmd *new);
void	replace_here_doc(char *file_name, t_redir *redir);
void	add_back_redir(t_redir **head_redir, t_redir *new);

/*  Executor  */
int		executor(t_minishell *mini);
void	exec_cmd(t_cmd *cmd, t_env **all_env, int *status);
int		process_loop(t_cmd *tmp, int pip[2], int *prev_pip, t_minishell *mini);

/*  Executor_utils  */
int		is_builtin(char *cmd);
int		do_in_redir(t_cmd *cmd);
int		do_out_redir(t_cmd *cmd);
int		process_just_redir(t_cmd *all_cmd);
int		exec_builtin(t_cmd *cmd, t_env **env);
int		only_one_blt(t_cmd *cmd, t_env **all_env);
char	*path(t_cmd *cmd, t_env *all_env, int *status);

/*  Signal  */
void	sig_dfl(void);
void	sig_ign(void);
void	sig_handler(int sig);
void	sig_main(struct sigaction sa);
t_sig	sig_init(void (*handler)(int));

/*  Clean  */
void	clean_cmd(t_cmd **cmd);
void	clean_env(t_env **all_env);
void	clean_tok(t_tok **all_tok);
void	clean_loop(char **line, t_minishell *mini);
void	clean_shell(char **line, t_minishell *mini);

/*  Error  */
void	error_exit_msg(char *msg, int status);

/*  Utils  */
char	*ft_itoa(int nb);
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

/* GNL */
char	*ft_free(char *s1);
char	*get_next_line(int fd);
char	*clean_stash_crop(char *s1);
char	*extract_line(const char *s1);
int		ft_strchr_gnl(const char *str);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strjoin_gnl(char *s1, const char *s2);
char	*ft_strcpy_gnl(char *dest, const char *src);
char	*read_to_stash(int fd, char *stash, char *buffer);

#endif