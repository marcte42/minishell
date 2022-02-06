/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:33:29 by pravry            #+#    #+#             */
/*   Updated: 2021/12/19 20:57:28 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	while (len != 0 && *haystack != '\0')
	{
		j = 0;
		while (haystack[j] == needle[j] && haystack[j] != '\0' && len - j != 0)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
