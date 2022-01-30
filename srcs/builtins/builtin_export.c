/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:09:53 by pravry            #+#    #+#             */
/*   Updated: 2022/01/30 19:15:36 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_env(char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

int	check_in_env(t_list *env, char *args, int error)
{
	char	*var;
	char	*env_name;

	var = get_key(args);
	if (error == 2)
		return (1);
	else
	{
		while (env && env->next)
		{	
			env_name = get_key(env->content);
			if (ft_strcmp(var, env_name) == 0)
			{
				free(env->content);
				env->content = ft_strdup(args);
				return (1);
			}
			env = env->next;
			free(env_name);
		}
	}
	free(var);
	return (SUCCESS);
}

void	env_add(char *arg, t_list *env)
{
	t_list	*node;	

	node = ft_lstnew(arg);
	ft_lstadd_back(&env, node);
}

int	ft_export(char	**args, t_list *env)
{
	int	error;
	int	new;

	new = 0;
	if (!args[1])
	{
		//put_sorted_env(env);
		return (SUCCESS);
	}
	else
	{
		error = check_valid_env(args[1]);
		if (args[1][0] == '=')
			error = -3;
		if (error <= 0)
		{
			ft_putstr_fd("error\n", STDERR_FILENO);
			return (0);
		}
		new = check_in_env(env, args[1], error);
		if (new == SUCCESS)
		{
			if (error == 1)
				env_add(args[1], env);
		}
	}
	return (SUCCESS);
}
