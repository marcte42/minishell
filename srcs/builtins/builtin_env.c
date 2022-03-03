/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:19:11 by acousini          #+#    #+#             */
/*   Updated: 2022/03/03 13:20:25 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_env(char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[0]) == 1 || env[0] == '=' || env[0] == '\0')
	{
		return (0);
	}
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0 && env[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_value_of_key(t_list *env, char *key)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (ft_strncmp(key, env->content, ft_strlen(key)) == 0)
		{
			if (((char *)env->content)[ft_strlen(key)] == '=')
				value = ft_strdup(ft_strchr(env->content, '=') + 1);
			return (value);
		}
		env = env->next;
	}
	return (value);
}

int	replace_env(t_list *env, char *args)
{
	char	*key;
	char	*env_name;
	char	*tmp;

	if (!env || !args)
		return (ERROR);
	key = get_key(args);
	while (env && key)
	{	
		env_name = get_key(env->content);
		if (env_name && ft_strcmp(key, env_name) == 0)
		{
			free(env_name);
			free(key);
			tmp = ft_strdup(args);
			if (!tmp)
				return (0);
			free(env->content);
			env->content = tmp;
			return (1);
		}
		env = env->next;
		ft_scott_free(&env_name, 1);
	}
	return (ft_scott_free(&key, 0));
}

int	ft_env(t_sys *mini, int fd)
{
	t_list	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (ft_findchar(tmp->content, '=') != -1)
		{
			ft_putstr_fd(tmp->content, fd);
			ft_putchar_fd('\n', fd);
		}
		tmp = tmp->next;
	}
	return (0);
}
