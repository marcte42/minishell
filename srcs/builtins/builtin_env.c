/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:19:11 by pravry            #+#    #+#             */
/*   Updated: 2022/02/06 22:48:52 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_env(char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[0]) == 1 || env[0] == '=')
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
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

	// go over with marc, do we free a whole elem?
int	replace_env(t_list *env, char *args)
{
	char	*var;
	char	*env_name;
	char	*tmp;

	if (!env || !args)
		return (ERROR);
	var = get_key(args);
	while (env)
	{	
		env_name = get_key(env->content);
		if (ft_strcmp(var, env_name) == 0)
		{
			free(env->content);
			tmp = ft_strdup(args);
		//	env->content = ft_strdup(args);
			free(env_name);
			free(var);				// free 1 env too? YES do that
			if (!tmp)
				return (ERROR);		// return success? just failed to update the thing...
			env->content = tmp;
			return (SUCCESS);
		}
		env = env->next;
		ft_scott_free(&env_name, 1);
	}
	ft_scott_free(&var, 1);
	return (ERROR);
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
