/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:28:11 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/29 11:53:17 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envlen(t_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;	
		i++;
	}
	return (i);
}

char **env_to_tab(t_list *env)
{
	char **tab;	
	int	i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_envlen(env) + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		tab[i] = ft_strdup(env->content);
		if (!tab[i])
		{
			while (--i >= 0)
				free(tab[i]);
			free(tab);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	*get_key(char *s)
{
	int		i;
	int		len;
	char	*key;

	len = 0;
	i = -1;	// isalnum, can env vars have numbers?
	while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_'))
		len++;
	key = malloc((len + 1) * sizeof(char));	// ft_memalloc
	if (!key)
		return (NULL);
	ft_strlcpy(key, s, len + 1);	// can it fail? no malloc
	return (key);
}

char	*expand_env(char *line, char *start, char *value)
{
	char	*tmp_line;
	int		key_len;
	int		line_len;
	int		value_len;
	int		i;

	key_len = 0;
	i = 0;
	while (start[++i] && (ft_isalnum(start[i]) || start[i] == '_'))
		key_len++;
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
	return (tmp_line);
}

char	*parse_env(char *line)
{
	int		i;
	char	*key;
	char	*value;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1] && !ft_isspace(line[i + 1])
			&& is_inquotes(line, &line[i]) != 1)
		{
			key = get_key(&line[i + 1]); // does this address all
											// edge cases?
			
			// "soemtho$HOME asdfasdf"


		// we need to do this
				// would it be better if we looked for env vals
				// just in our list of envs?
				// since can export and unset?
			value = getenv(key);// can it fail?
			// is it fine if send the whole line, "sfda$HOME someth"
			free(key);	// ft_scott_free for case when key is null
			line = expand_env(line, &line[i], value);
			if (!line)
				return (NULL);
			i = -1;
		}
	}
	return (line);
}
