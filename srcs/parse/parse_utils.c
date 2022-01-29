/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:46:21 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/28 15:41:50 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	// double check secure frees
char	*add_space(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc((strlen(str) + (count_redirs(str) * 2) + 1) * sizeof(char));
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (!is_inquotes(str, &str[i]) && (!strncmp(&str[i], "<<", 2) || !strncmp(&str[i], ">>", 2)))
		{
			new_str[j] = ' ';
			new_str[j + 1] = str[i];
			new_str[j + 2] = str[i + 1];
			new_str[j + 3] = ' ';
			i++;
			j += 3;
		}
		else if (!is_inquotes(str, &str[i]) && (!strncmp(&str[i], "<", 1) || !strncmp(&str[i], ">", 1)))
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
	return (new_str);
}
