/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:28:11 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/11 02:17:10 by me               ###   ########.fr       */
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

int	ft_has_valid_env(t_sys *mini, char *line)
{

	// helpful for testing but no longer necessary
	int	i;
	char	*key;
	char	*value;

	i = -1;
	while (line && line[++i])
	{
		if (line[i] == '$' && line[i + 1] && is_inquotes(line, &line[i]) != 1
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
		{
			key = get_key(&line[i + 1]);
			if (!key)
				return (0);
			value = ft_getenv(mini, key, mini->env);
	//		printf("value: %s\n", value);
			if (!value || value[0] == '\0')	// free key? might need a special free that returns null so can return it here
			{
				free(key);
				return (ft_scott_free(&value, 2));
			}
			free(key);
			i = i + ft_strlen(value) - 1;
			free(value);
			return (1);
		}
	}
	return (0);
}

void	*ft_free_ret_null(char *thing)
{
	if (thing)
		free(thing);
	return (NULL);
}


char	*parse_env(t_sys *mini, char *line, t_list *env)
{
	int		i;
	char	*key;
	char	*value;

//	printf("in pars env\n");
	i = -1;
	while (line && line[++i])
	{
	//	printf("line: |%s|\n", &line[i]);
		if (line[i] == '$' && line[i + 1] && is_inquotes(line, &line[i]) != 1
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
		{
		//	printf("line: |%s|\n", &line[i]);
			key = get_key(&line[i + 1]);
			if (!key)
				return (NULL);
			value = ft_getenv(mini, key, env);
			if (!value)	// free key? might need a special free that returns null so can return it here
				return (ft_free_ret_null(value));
	//			return (NULL);
			line = expand_env(line, &line[i], key, value);
			free(key);
			i = i + ft_strlen(value) - 1;
			free(value);
			if (!line)
				return (NULL);
		}
	}
	return (line);
}
