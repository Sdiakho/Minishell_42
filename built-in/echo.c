/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:58:16 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/23 14:47:03 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_token(char *param, int *flag)
{
	int	i;

	i = 1;
	while (param[i] != '\0')
	{
		if (param[i] != 'n')
		{
			*flag = 2;
			break ;
		}
		i++;
	}
	if (param[i] == '\0')
		*flag = 1;
}

void	print_tokens(char **tokens, int flag, int *i)
{
	while (tokens[*i])
	{
		if (tokens[*i + 1] != NULL)
			printf("%s ", tokens[*i]);
		else if (flag == 1)
			printf("%s", tokens[*i]);
		else
			printf("%s\n", tokens[*i]);
		(*i)++;
	}
}

void	check_tokens(char **tokens, int *flag, int *i)
{
	int	j;

	while (tokens[*i])
	{
		if (*flag == -1 || *flag == 1)
		{
			j = 0;
			if (tokens[*i][j] == '-' && tokens[*i][j + 1] != '\0')
				check_token(tokens[*i], flag);
			else
				break ;
		}
		else
			break ;
		if (*flag == 2)
			break ;
		(*i)++;
	}
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	if (!cmd->cmd_param[1])
	{
		printf("\n");
		return (0);
	}
	i = 1;
	flag = -1;
	check_tokens(cmd->cmd_param, &flag, &i);
	print_tokens(cmd->cmd_param, flag, &i);
	return (0);
}

// int	ft_echo(t_cmd *cmd)
// {
// 	int	i;
// 	int	j;
// 	int flag;

// 	if (!cmd->cmd_param[1])
// 	{
// 		printf("\n");
// 		return (0);
// 	}
// 	i = 1;
// 	flag = -1;
// 	while (cmd->cmd_param[i])
// 	{
// 		if (flag == -1 || flag == 1)
// 		{
// 			j = 0;
// 			if (cmd->cmd_param[i][j] == '-' && cmd->cmd_param[i][j + 1] != '\0')
// 			{
// 				j = 1;
// 				while (cmd->cmd_param[i][j])
// 				{
// 					if (cmd->cmd_param[i][j] != 'n')
// 					{
// 						flag = 2;
// 						break ;
// 					}
// 					j++;
// 				}
// 				if (cmd->cmd_param[i][j] == '\0')
// 					flag = 1;
// 			}
// 			else
// 			{
// 				flag = 2;
// 				break ;
// 			}
// 		}
// 		else
// 			break ;
// 		if (flag == 2)
// 			break ;
// 		i++;
// 	}
// 	while (cmd->cmd_param[i])
// 	{
// 		if (cmd->cmd_param[i + 1] != NULL)
// 		{
// 			printf("%s ", cmd->cmd_param[i]);
// 		}
// 		else if (flag == 1)
// 			printf("%s", cmd->cmd_param[i]);
// 		else
// 			printf("%s\n", cmd->cmd_param[i]);
// 		i++;
// 	}
// 	return (0);
// }