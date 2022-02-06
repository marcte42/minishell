/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:47:04 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/06 19:33:08 by mterkhoy         ###   ########.fr       */
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
			if (!str[i])
				return (0);
		}
	}
	return (!open);
}

void	trim_quote(char *str, int *i)
{
	ft_memmove(&str[*i], &str[*i + 1], strlen(&str[*i]));
	(*i)--;
}

void	trim_quotes(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	if (!str)
		return ;
	s_quote = 0;
	d_quote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && !d_quote && ++s_quote)
			trim_quote(str, &i);
		else if (str[i] == '\"' && !s_quote && ++d_quote)
			trim_quote(str, &i);
		else if (str[i] == '\'' && !d_quote && s_quote--)
			trim_quote(str, &i);
		else if (str[i] == '\"' && !s_quote && d_quote--)
			trim_quote(str, &i);
	}
}
