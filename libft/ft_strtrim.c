/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:35:44 by pravry            #+#    #+#             */
/*   Updated: 2019/12/08 17:41:24 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_check(char s, char const *set)
{
	while (*set)
	{
		if (s == *set)
			return (0);
		set++;
	}
	return (1);
}

static int	ft_start(const char *s, const char *set)
{
	int start;
	int	i;

	i = 0;
	start = 0;
	while (ft_check(s[i], set) == 0 && s[i])
	{
		i++;
		start++;
	}
	return (start);
}

static int	ft_end(const char *s, const char *set)
{
	int	end;

	end = ft_len((char *)s);
	while (s[end - 1] && s[end - 1] && ft_check(s[end - 1], set) == 0)
		end--;
	return (end);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = ft_start(s1, set);
	if (!s1 || !set)
		return (ft_strdup(""));
	if (s1[i] == '\0')
	{
		if (!(tmp = malloc(1)))
			return (NULL);
		tmp[0] = '\0';
		return (tmp);
	}
	tmp = (char *)malloc(sizeof(char) * ((ft_end(s1, set) - i) + 1));
	if (tmp == NULL)
		return (NULL);
	while (s1[i] && i < ft_end(s1, set))
	{
		tmp[j++] = s1[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}
