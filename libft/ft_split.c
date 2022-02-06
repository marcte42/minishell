/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:36:48 by pravry            #+#    #+#             */
/*   Updated: 2021/12/19 23:02:40 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(int i, char **result)
{
	int	j;

	j = 0;
	while (j < i)
		free(result[j++]);
	free(result);
}

static int	ft_size_malloc(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count + 1);
}

static char	*ft_line(char *s, char c)
{
	char	*line;
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (ft_size_malloc((char *)s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s && *s != c)
		{
			result[i++] = ft_line((char *)s, c);
			if (result[i - 1] == NULL)
			{
				ft_free(i - 1, result);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
	}
	result[i] = 0;
	return (result);
}
