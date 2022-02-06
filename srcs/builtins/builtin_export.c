/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 21:19:56 by me                #+#    #+#             */
/*   Updated: 2022/02/02 10:28:25 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in BASH if export test and run export no args it prints " test "
// but if export test= and run export no args it prints " test="" "
// fuck...

int	check_valid_env(char *env)		// checks if the requested env is a valid format, so like no = and only 
{
	int	i;

	i = 0;
	if (ft_isdigit(env[0]) == 1 || env[0] == '=')	// i'll be honest i don't see the point of this...
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (0);
		i++;
	}
	if (env[i] != '=' || i == (int)ft_strlen(env))
		return (0);
	return (1);
}

// contents has a strings

int	replace_env(t_list *env, char *args)	// why do we send error?
{
	t_list	*node;	// it seemed to work fine without node...
	char	*var;
	char	*env_name;

	if (!env || !args)
		return (ERROR);
	node = env;
	var = get_key(args);

//	while (env && env->next)
	while (node)
	{	
		env_name = get_key(node->content);	// do i need to free env_name if failure? it'll just get freed at the end anyway...
	//	printf("env_name: %s\nnode->content: %s\n", env_name, (char *)node->content);
		if (ft_strcmp(var, env_name) == 0)
		{
		//	printf("env_name: %s\nnode->content: %s\n", env_name, (char *)node->content);
			free(node->content);
			node->content = ft_strdup(args);
			if (!node->content)
			{
				free(env_name);
				free(var);	// free 1 env too? YES do that
				return (ERROR);
			}
			return (SUCCESS);
		}
		node = node->next;
		free(env_name);
	}
	free(var);
	return (ERROR);
}

int	env_add(char *arg, t_list *env)
{
	t_list	*node;
	char	*tmp;

//	printf("making a new node, arg: %s\n", arg);
	tmp = ft_strdup(arg);
	if (!tmp)
		return (ERROR);
	node = ft_lstnew(tmp);
	if (!node)
	{
		free(tmp);
		return (ERROR);
	}
	ft_lstadd_back(&env, node);
//	printf("contents: %s\n", (char*)node->content);
	return (SUCCESS);
}

/*
int	get_value(char *env, int)
{
	int	i;

	if (!env)
		return (0);
	i = 


	return 
}
*/


int	print_envs(t_list *env)
{
	t_list	*tmp;
	char	*key;
	char	*value;

	// prolly should send a sorted list

	if (!env)
		return (SUCCESS);	// do we print an empty line? no i think we just move on to the next one

	// create a new sorted list...
	tmp = env;
	value = NULL;
	while (tmp)
	{	// decide how to handle this...
		key = get_key(tmp->content);
		if (!key)
			return (ERROR);
	//	value = ft_substr(tmp->content, ft_strlen(key) + 1, ft_strlen(tmp->content) - ft_strlen(key) - 1);
//		if (!key || !value)
//			return (ERROR);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);	// double check that this is the right message on Linux too.
		ft_putstr_fd(key, STDOUT_FILENO);
		if (ft_strlen(tmp->content) > ft_strlen(key))
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
	//		value = ft_substr(tmp->content, ft_strlen(key) + 1, ft_strlen(tmp->content) - ft_strlen(key) - 1);
			ft_putstr_fd(value, STDOUT_FILENO);		// in theory this works for when env var is empty
			ft_putstr_fd("\"\n", STDOUT_FILENO);
		}
		free(key);
		ft_scott_free(&value, 1);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

// do i want to check if the Env Var already exists?

int	ft_export(char	**args, t_list *env)
{
//	int	error;
	// int	new;

	// new = 0;
	if (!args[1])	// so far so good
	{
		//put_sorted_env(env);
		return (print_envs(env));
	//	return (SUCCESS);
	}
	else
	{
		//printf("args[1]: %s\n", args[1]);
		if (!check_valid_env(args[1]))
			return (ERROR);	// error or do nothing? so SUCCESS?
		
		if (!replace_env(env, args[1]))
		{
			if (!env_add(args[1], env))	// love the redundancy
				return (ERROR);
		}
	}
	return (SUCCESS);
}
