/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:47:04 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/28 15:21:03 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
	return (0);
}

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

void	trim_quote(char *str, int *i, int *is_open)
{
	ft_memmove(&str[*i], &str[*i + 1], ft_strlen(&str[*i]));
	(*i)--;
	if (*is_open != 0)
		*is_open = 0;
	else
		*is_open = 1;
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
	if (!control_quotes(str))
		return ;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && !d_quote)
			trim_quote(str, &i, &s_quote);
		else if (str[i] == '\"' && !s_quote)
			trim_quote(str, &i, &d_quote);
	}
}
