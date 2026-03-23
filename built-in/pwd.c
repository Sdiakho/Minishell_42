/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 22:32:42 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/22 23:27:57 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	buffer_path[1024];

	if (getcwd(buffer_path, 1024) == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", buffer_path);
	return (0);
}
