/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 21:12:21 by pravry            #+#    #+#             */
/*   Updated: 2021/12/19 21:02:20 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		size;
	int		i;

	i = 0;
	size = ft_len((char *)s1);
	cpy = (char *)malloc(sizeof(char) * size + 1);
	if (cpy != NULL)
	{
		while (i < size)
		{
			cpy[i] = s1[i];
			i++;
		}
		cpy[i] = '\0';
		return (cpy);
	}
	else
		return (NULL);
}
