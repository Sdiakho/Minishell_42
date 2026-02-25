/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:31:16 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/25 12:10:22 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

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

/*  Env  */
void	env(t_env **all_env);
int		search_key(char *str);
void	alloc_name(t_env **env, char *str);
t_env	*fill_env(char **envp, t_env **all_env);
void	alloc_env(t_env **env, char *str, int sep);
/** Env_List  **/
t_env	*create_node(void);
void	add_front(t_env	**head, t_env *new);

/*  Utils  */
int		ft_strlen(const char *str);
char	*ft_strnndup(char *src, int start, int end);

#endif