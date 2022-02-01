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

// no idea what the correct exit codes are for this builtin

// Ok here's what i understand so far:
// you don't want the first char of an env var to be a digit
// but it's fine after that.
// there has to be a =
//


int	check_valid_env(char *env)		// checks if the requested env is a valid format, so like no = and only 
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)	// i'll be honest i don't see the point of this...
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

int	check_in_env(t_list *env, char *args, int error)	// why do we send error?
{
	char	*var;
	char	*env_name;

	var = get_key(args);
	if (error == 2)		// this seems fucking dumb... and we aren't freeing...
		return (1);		// just replace with free var
	else
	{
		while (env && env->next)
		{	
			env_name = get_key(env->content);
			if (ft_strcmp(var, env_name) == 0)
			{
				free(env->content);		// marc said there was a problem with this
				env->content = ft_strdup(args);	// doesn't work cuz ours 
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
		printf("args[1]: %s\n", args[1]);
		error = check_valid_env(args[1]);
		if (args[1][0] == '=')	// seems redundant, could prolly rework this shit...
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
