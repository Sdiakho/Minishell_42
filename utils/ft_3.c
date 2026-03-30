/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:12:53 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/28 14:21:28 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strschr(char *str, char *chr)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (chr[j])
		{
			if (str[i + j] == chr[j])
				j++;
			else
				break ;
		}
		if (j == ft_strlen(chr))
			return (1);
		i++;
	}
	return (0);
}

char	*process_0(void)
{
	char	*zero;

	zero = (char *)malloc(2);
	if (!zero)
		return (NULL);
	zero[0] = '0';
	zero[1] = '\0';
	return (zero);
}

char	*ft_itoa(int nb)
{
	char	*nbr;
	int		len;
	long	nb_l;

	if (nb == 0)
		return (process_0());
	nb_l = nb;
	len = 0;
	while (nb_l != 0)
	{
		len++;
		nb_l /= 10;
	}
	nbr = (char *)malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len] = '\0';
	len--;
	while (nb != 0)
	{
		nbr[len] = (nb % 10) + '0';
		len--;
		nb /= 10;
	}
	return (nbr);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
