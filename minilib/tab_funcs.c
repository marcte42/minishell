/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 19:59:16 by ericlazo          #+#    #+#             */
/*   Updated: 2022/02/14 02:28:31 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

int	ft_free_strtab(char **tab)
{
	int		a;

	a = 0;
	if (!tab || !*tab)
		return (0);
	while (tab[a])
	{
		ft_scott_free(&(tab[a]), 1);
		++a;
	}
	return (1);
}

int	ft_print_strtab(char **tab)
{
	int		a;

	if (!tab)
		return (0);
	a = 0;
	while (tab[a])
	{
		write(1, tab[a], ft_strlen(tab[a]));
		write(1, "\n", 1);
		++a;
	}
	return (1);
}

int	strtab_len(char **tab)
{
	int	i;

	if (!tab)
		return (-1);
	i = 0;
	while (tab[i])
		++i;
	return (i);
}

int	add_str(char *to_add, char **to_fill, int *a)
{
	int	b;

	b = -1;
	while (to_add[++b])
	{
		(*to_fill)[++(*a)] = to_add[b];
	}
	return (1);
}

char	*concat_tab_strs(char **tab)
{
	int		i;
	int		a;
	int		len;
	char	*ret;

	if (!tab || !*tab)
		return (NULL);
	i = -1;
	len = 0;
	while (tab[++i])
		len += ft_strlen(tab[i]);
	ret = (char *)calloc(len + i, sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	a = -1;
	while (tab[++i])
	{
		add_str(tab[i], &ret, &a);
		if (tab[i + 1])
			ret[++a] = ' ';
	}
	return (ret);
}
