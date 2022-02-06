/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:47:09 by pravry            #+#    #+#             */
/*   Updated: 2021/12/19 21:10:09 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy2(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest2;
	unsigned char	*src2;

	dest2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*src;
	char		*dst;

	src = s2;
	dst = s1;
	if (dst > src)
	{
		i = n;
		while (i > 0)
		{
			dst[i - 1] = src[i - 1];
			i--;
		}
	}
	else if (dst < src)
		ft_memcpy2(dst, src, n);
	return (s1);
}
