/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:47:04 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/29 16:56:40 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_inquotes(char *s, char *c)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = 0;
		if (s[i] == '\'')
		{
			while (s[i + ++j] && s[i + j] != '\'')
				if (&s[i + j] == c)
					return (1);
		}
		else if (s[i] == '\"')
		{
			while (s[i + ++j] && s[i + j] != '\"')
				if (&s[i + j] == c)
					return (2);
		}
		i += j;
	}
	return (0);
}

int	control_quotes(char *str)
{
	int	i;
	int	tmp;
	int	open;

	open = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			open = 1;
			tmp = i;
			while (str[++i])
			{
				if (str[tmp] == str[i])
				{
					open = 0;
					break ;
				}
			}
		}
	}
	return (!open);
}

char	*trim_quotes(char *str)
{
	int		len;
	char	*newstr;

	if (str[0] == '\"' || str[0] == '\'')
	{
		len = strlen(str);
		if (len == 1 || str[0] != str[len - 1])
			return (NULL);
		else
		{
			newstr = malloc((len - 1) * sizeof(char));
			if (!newstr)
				return (NULL);
			strncpy(newstr, &str[1], len - 2);
			newstr[len - 2] = 0;
			return (newstr);
		}
	}
	newstr = ft_strdup(str);
	if (!newstr)
		return (NULL);
	return (newstr);
}

