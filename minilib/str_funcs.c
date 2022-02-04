/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 19:44:54 by ericlazo          #+#    #+#             */
/*   Updated: 2022/01/19 05:47:11 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

int	ft_findchar(char *str, char c)
{
	int		i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

char	*ft_mstrjoin(char *s1, char *s2)
{
	int		a;
	int		c;
	char	*ret;

	ret = NULL;
	if (!s1 && !s2)
		return (NULL);
	a = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)ft_calloc(a, sizeof(char));
	if (!ret)
		return (NULL);
	a = 0;
	c = 0;
	while (s1 && s1[c])
	{
		ret[a++] = s1[c];
		++c;
	}
	while (s2 && *s2)
	{
		ret[a++] = *s2;
		++s2;
	}
	return (ret);
}
