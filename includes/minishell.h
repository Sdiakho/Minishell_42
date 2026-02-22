/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:31:16 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/22 16:49:09 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


/* 1. Structure pour représenter UNE redirection */
typedef struct s_redir {
    int             type;
    char            *file;
    struct s_redir  *next;
} t_redir;

typedef struct s_cmd {
    char            **cmd_param;
    t_redir         *redirs;
    int             fd_in;
    int             fd_out;
    struct s_cmd    *next;
} t_cmd;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next; 
}					t_env;