/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:01:48 by pravry            #+#    #+#             */
/*   Updated: 2021/05/27 13:51:24 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_tab(char **tab)
{
	int	i;

	if (!**tab || !*tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

static char	**join_next(char **new, char **tmp, size_t i, size_t tmp_len)
{
	size_t	j;

	j = -1;
	while (++j < tmp_len)
	{
		new[i + j] = ft_strdup(tmp[j]);
		if (!new[i + j])
			ft_free_tab(new);
	}
	new[i + j] = NULL;
	return (new);
}

char		**ft_tab_join(char **tab, char **tmp)
{
	char	**new;
	size_t	tab_len;
	size_t	tmp_len;
	size_t	i;

	i = -1;
	tab_len = ft_tab_len(tab);
	tmp_len = ft_tab_len(tmp);
	new = (char **)malloc(sizeof(char *) * (tab_len + tmp_len + 1));
	if (!new)
		return (NULL);
	while (++i < tab_len)
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			ft_free_tab(new);
	}
	if (tab)
		ft_free_tab(tab);
	return (join_next(new, tmp, i, tmp_len));
}
