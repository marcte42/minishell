/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:46:21 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/10 21:33:35 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isempty(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = -1;
	while (s[++i])
	{
		if (!ft_isspace(s[i]))
			return (0);
	}
	return (1);
}

int	count_pipes(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' && !is_inquotes(s, &s[i]))
			count++;
	}
	return (count);
}

int	count_redirs(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
		{
			count++;
			i++;
		}
		else if (str[i] == '>' || str[i] == '<')
			count++;
		i++;
	}
	return (count);
}

void	insert_space(char *str, char *new_str, int i, int j)
{
	while (str[++i])
	{
		if (!is_inquotes(str, &str[i]) && (!ft_strncmp(&str[i], "<<", 2)
				|| !ft_strncmp(&str[i], ">>", 2)))
		{
			new_str[j] = ' ';
			new_str[j + 1] = str[i];
			new_str[j + 2] = str[i + 1];
			new_str[j + 3] = ' ';
			i++;
			j += 3;
		}
		else if (!is_inquotes(str, &str[i]) && (!ft_strncmp(&str[i], "<", 1)
				|| !ft_strncmp(&str[i], ">", 1)))
		{
			new_str[j] = ' ';
			new_str[j + 1] = str[i];
			new_str[j + 2] = ' ';
			j += 2;
		}
		else
			new_str[j] = str[i];
		j++;
	}
	new_str[j] = 0;
}

char	*add_space(char *str)
{
	char	*new_str;

	new_str = malloc((ft_strlen(str) + (count_redirs(str) * 2) + 1)
			* sizeof(char));
	if (!new_str)
		return (NULL);
	insert_space(str, new_str, -1, 0);
	return (new_str);
}
