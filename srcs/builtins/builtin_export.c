/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:09:53 by pravry            #+#    #+#             */
/*   Updated: 2021/06/28 11:47:29 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	check_in_env(t_envi *env, char *args, int error)
{
	char	*var;
	char	*env_name;
	
	var = get_env_name(args);
	if (error == 2)
		return (1);
	else
	{
		while (env && env->next)
		{	
			env_name = get_env_name(env->value);
			if (ft_strcmp(var, env_name) == 0)
			{
				free(env->value);
				env->value = ft_strdup(args);
				return (1);
			}
			env = env->next;
			free(env_name);
		}
	}
	free(var);
	return (SUCCESS);
}

void	env_add(char *arg, t_envi *env)
{
	t_envi *new;
	t_envi *tmp;	

	new = new_elem(arg);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
}

int	ft_export(char	**args, t_envi *env)
{
	int	error;
	int	new;

	new = 0;
	if (!args[1])
	{
		put_sorted_env(env);
		return (SUCCESS);
	}
	else
	{
		error = check_valid_env(args[1]);
		if (args[1][0] == '=')
			error = -3;
		if (error <= 0)
		{
			printf("error\n");
			return (0);
		}
		new = check_in_env(env, args[1], error);
		printf("%d\n", new);
		if (new == 0)
		{
			if (error == 1)
				env_add(args[1], env);
		}
	}
	return (SUCCESS);
}
