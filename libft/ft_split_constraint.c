/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_constraint.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:02:20 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/03/03 14:04:45 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free(int i, char **result)
{
	int	j;

	j = 0;
	while (j < i)
		free(result[j++]);
	free(result);
	return (NULL);
}

static int	ft_size_malloc(char *s, char c, int (*except)(char *s, char *c))
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && !except(s, &s[i]))
			count++;
		i++;
	}
	return (count + 1);
}

static char	*ft_line(char *s, char c, int (*except)(char *s, char *c))
{
	char	*line;
	int		i;

	i = 0;
	while (s[i] && (s[i] != c || except(s, &s[i])))
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && (s[i] != c || except(s, &s[i])))
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	**ft_split_constraint(char *s, char c, int (*except)(char *s, char *c))
{
	char	**result;
	int		i;
	int		j;

	result = (char **)ft_calloc(sizeof(char *), \
			(ft_size_malloc((char *)s, c, except) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c && !except(s, &s[j]) && *s)
			j++;
		if (s[j] && (s[j] != c || except(s, &s[j])))
		{
			result[i] = ft_line(&s[j], c, except);
			if (!result[i++])
				return (ft_free(i - 1, result));
			while (s[j] && (s[j] != c || except(s, &s[j])))
				j++;
		}
	}
	return (result);
}
