/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:10:44 by sdiakho           #+#    #+#             */
/*   Updated: 2026/03/26 18:35:05 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*new_ptr;

	total_size = count * size;
	if (total_size == 0)
		return (NULL);
	new_ptr = (char *)malloc(total_size);
	if (!new_ptr)
		return (NULL);
	ft_bzero(new_ptr, total_size);
	return (new_ptr);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*join;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!join || (!s1 && !s2))
		return (NULL);
	if (s1)
		ft_strlcopy(join, s1, len_s1 + 1);
	if (s2)
		ft_strlcopy(&join[len_s1], s2, len_s2 + 1);
	return (join);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
