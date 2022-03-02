/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:56:57 by acousini          #+#    #+#             */
/*   Updated: 2022/03/02 18:52:27 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*res;
	unsigned int		i;

	if (s)
	{
		res = (char *)malloc((sizeof(char) * (ft_len(s) + 1)));
		if (res == NULL)
			return (NULL);
		i = 0;
		while (s[i])
		{
			res[i] = (*f)(i, ((char)s[i]));
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	res = NULL;
	return (res);
}
