/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:36:39 by acousini          #+#    #+#             */
/*   Updated: 2022/03/02 18:52:27 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;
	size_t			i;

	t1 = (unsigned char *)dest;
	t2 = (unsigned char *)src;
	i = 0;
	c = (unsigned char)c;
	while (i < n)
	{
		*t1 = *t2;
		t2++;
		t1++;
		if (*t2 == c)
		{
			*t1 = *t2;
			return (t1 + 1);
		}
		i++;
	}
	return (NULL);
}
