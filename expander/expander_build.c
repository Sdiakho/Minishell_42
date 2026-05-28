/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiakho <sdiakho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:25:53 by sdiakho           #+#    #+#             */
/*   Updated: 2026/05/28 12:12:52 by sdiakho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*create_empty_value(void)
{
	char	*empty;

	empty = (char *)malloc(sizeof(char) * 1);
	if (!empty)
		return (NULL);
	empty[0] = '\0';
	return (empty);
}

static char	*safe_dup_value(char *value)
{
	if (!value)
		return (create_empty_value());
	return (ft_strnndup(value, 0, ft_strlen(value)));
}

char	*get_env_value(char *key, t_env *all_env)
{
	t_env	*tmp;
	int		key_len;
	int		skey_len;

	tmp = all_env;
	skey_len = ft_strlen(key);
	while (tmp)
	{
		key_len = ft_strlen(tmp->name);
		if (skey_len == key_len
			&& ft_strncmp(key, tmp->name, key_len) == 0)
			return (free(key), safe_dup_value(tmp->value));
		tmp = tmp->next;
	}
	free(key);
	return (create_empty_value());
}

char	*create_swap(char *str, char *swap)
{
	int		pos_dl;
	int		len_str;
	int		len_var;
	char	*temp;
	char	*full_join;

	pos_dl = check_env_var(str);
	if (pos_dl == -1)
		return (NULL);
	len_str = ft_strlen(str);
	len_var = get_var_len(&str[pos_dl + 1]);
	temp = (char *)malloc(sizeof(char) * (ft_strlen(swap) + pos_dl + 1));
	if (!temp)
		return (NULL);
	ft_strlcopy(temp, str, pos_dl + 1);
	ft_strlcopy(&temp[pos_dl], swap, ft_strlen(swap) + 1);
	full_join = (char *)malloc((ft_strlen(temp)
				+ len_str - pos_dl - len_var + 1));
	if (!full_join)
		return (free(temp), NULL);
	ft_strlcopy(full_join, temp, ft_strlen(temp) + 1);
	ft_strlcopy(full_join + ft_strlen(temp), str + pos_dl + len_var + 1,
		len_str - pos_dl - len_var + 1);
	free(temp);
	return (full_join);
}
