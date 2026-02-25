/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 09:35:21 by sdiakho           #+#    #+#             */
/*   Updated: 2026/02/25 12:06:59 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	clean_env(t_env **all_env)
// {
// 	t_env *tmp;
// 	t_env *tmp2;
//
// 	if (!all_env || !(*all_env))
// 		return ;
// 	tmp2 = *all_env;
// 	while (tmp)
// 	{
// 		tmp2 = tmp;
// 		if (tmp->name)
// 			free(tmp->name);
// 		if (tmp->value)
// 			free(tmp->value);
// 		tmp2 = tmp->next;
// 		free(tmp);
// 	}
// }
