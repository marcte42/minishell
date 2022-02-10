/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:28:11 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/10 13:59:12 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(char *line, char *start, char *key, char *value)
{
	char	*tmp_line;
	int		key_len;
	int		line_len;
	int		value_len;
	int		i;

	key_len = ft_strlen(key);
	line_len = ft_strlen(line);
	value_len = ft_strlen(value);
	tmp_line = ft_calloc((line_len - key_len + value_len), sizeof(char));
	if (!tmp_line)
		return (NULL);
	i = -1;
	while (line[++i] && &line[i] != start)
		tmp_line[i] = line[i];
	if (value)
		ft_strcat(tmp_line, value);
	ft_strcat(tmp_line, &start[key_len + 1]);
	free(line);
	return (tmp_line);
}

char	*parse_env_heredoc(t_sys *mini, char *line, t_list *env)
{
	int		i;
	char	*key;
	char	*value;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
		{
			key = get_key(&line[i + 1]);
			if (!key)
				return (NULL);
			value = ft_getenv(mini, key, env);
			if (!value)
				return (NULL);
			line = expand_env(line, &line[i], key, value);
			free(key);
			free(value);
			if (!line)
				return (NULL);
			i = -1;
		}
	}
	return (line);
}

char	*parse_env(t_sys *mini, char *line, t_list *env)
{
	int		i;
	char	*key;
	char	*value;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1] && is_inquotes(line, &line[i]) != 1
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
		{
			key = get_key(&line[i + 1]);
			if (!key)
				return (NULL);
			value = ft_getenv(mini, key, env);
			if (!value)
				return (NULL);
			line = expand_env(line, &line[i], key, value);
			free(key);
			free(value);
			if (!line)
				return (NULL);
			i = i + ft_strlen(value) - 1;
		}
	}
	return (line);
}
