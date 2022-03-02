/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:33:50 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/03/02 19:05:28 by acousini         ###   ########.fr       */
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

int	is_dir(char *path)
{
	int	fd;

	errno = 0;
	fd = open(path, O_WRONLY);
	if (errno == EISDIR)
		return (1);
	if (fd > 0)
		close(fd);
	return (0);
}

int	special_mini_error(char *file, int ret)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (ret);
}
