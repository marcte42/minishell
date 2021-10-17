/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:14:43 by pravry            #+#    #+#             */
/*   Updated: 2019/11/17 18:41:18 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(const char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

char		*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_len(s);
	while (i > -1)
	{
		if (s[i] == (unsigned char)c)
			return ((char*)s + i);
		i--;
	}
	return (0);
}
