/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:11:43 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/30 21:28:35 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_args(char **args)
{
	if (args[1] == NULL)
		return (1);
	if (args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		return (0);
	}
	return (1);
}

int	numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (0);
}

int	check_arg(char *arg)
{
	int	i;

	if (!arg)
		return (1);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i + 1] == '\0')
			return (numeric_error(arg));
		i++;
	}
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (numeric_error(arg));
		i++;
	}
	return (1);
}

int	ft_atoi(char *str, int *out)
{
	unsigned long	res;
	long			sign;

	if (!str || !out)
		return (0);
	while (is_space(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	if (!is_digit(*str))
		return (0);
	res = 0;
	while (is_digit(*str))
	{
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > LONG_MAX) || (sign == -1 && res > LONG_MIN))
			return (0);
	}
	while (is_space(*str))
		str++;
	if (*str)
		return (0);
	return (*out = ((int)(res * sign) % 256), 1);
}

int	ft_exit(t_cmd *cmd, t_minishell *mini)
{
	int		status;
	char	*empty_ptr;

	empty_ptr = NULL;
	ft_putstr_fd("exit\n", 1);
	if (!check_arg(cmd->cmd_param[1]))
		status = 255;
	else if (!check_args(cmd->cmd_param))
		return (1);
	else if (cmd->cmd_param[1] == NULL)
		status = mini->exit_status;
	else if (!ft_atoi(cmd->cmd_param[1], &status))
	{
		numeric_error(cmd->cmd_param[1]);
		status = 255;
	}
	clean_shell(&empty_ptr, mini);
	exit(status);
}
