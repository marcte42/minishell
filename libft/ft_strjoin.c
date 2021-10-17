/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:21:57 by pravry            #+#    #+#             */
/*   Updated: 2019/12/08 17:32:56 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		j;
	int		i;

	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(s1) * (ft_len(s1) + ft_len(s2) + 1));
	if (dst == NULL)
		return (NULL);
	while (s1[j])
	{
		dst[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}
