/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:28:11 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/07 17:36:59 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_tab(t_list *env)
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
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

	if (*s == '?')
		return (ft_strdup("?"));
	len = 0;
	i = -1;
	while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_'))
		len++;
	key = malloc((len + 1) * sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, s, len + 1);
	return (key);
}

// ft_getenv
// Retourne un char* avec la valeur associee a la key
// Si la key n'a pas ete trouvee on retourne un char* vide ""
// Si une erreur se produit on retourne un NULL
char	*ft_getenv(t_sys *mini, char *key, t_list *env)
{
	char	*env_key;
	char	*ptr;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(mini->retval));
	while (env)
	{
		env_key = get_key(env->content);
		if (!env_key)
			return (NULL);
		if (ft_strcmp(key, env_key) == 0)
		{
			free(env_key);
			ptr = ft_strchr(env->content, '=');
			if (!ptr)
				return (ft_strdup(""));
			return (ft_strdup(ptr + 1));
		}
		free(env_key);
		env = env->next;
	}
	return (ft_strdup(""));
}

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
			i = -1;
		}
	}
	return (line);
}
