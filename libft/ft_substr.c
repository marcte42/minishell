/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:28:22 by pravry            #+#    #+#             */
/*   Updated: 2019/12/08 17:30:15 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_len(char const *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	unsigned int	i;

	i = 0;
	dst = (char *)malloc((sizeof(char)) * (len + 1));
	if (dst == NULL)
		return (NULL);
	if (start > ft_len(s))
	{
		dst[i] = '\0';
		return (dst);
	}
	while (s[i + start] && len)
	{
		dst[i] = s[i + start];
		len--;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
