/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 21:19:56 by me                #+#    #+#             */
/*   Updated: 2022/02/03 03:56:33 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// might need to modify
int	check_valid_env(char *env)		// checks if the requested env is a valid format, so like no = and only 
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
//	if (env[i] != '=' || i == (int)ft_strlen(env))
//	if (i == (int)ft_strlen(env))
//		return (0);
	return (1);
}

// contents has a strings
// could move this to CD, would save space here
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
		free(env_name);
	}
	free(var);
	return (ERROR);
}

int	add_env_elem(char *arg, t_list *env)
{
	t_list	*node;
	char	*tmp;

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
	return (SUCCESS);
}

t_list	*ft_lstdup(t_list *lst)
{
	t_list *nlist;
	t_list	*new;

	nlist = NULL;
	while (lst)
	{
		new = ft_lstnew(lst->content);
		if (!new)
		{
			ft_lstclear(&nlist, free);
			return (NULL);
		}
		ft_lstadd_back(&nlist, new);
		lst = lst->next;
	}
	return (nlist);
}

// just used for testing
/*
t_list	*test_list(char *str)
{
	t_list	*new;
	t_list	*ret;
	int		i;
	char	**tab;

	ret = NULL;
	tab = ft_split(str, ' ');
	i = 0;
	while (tab[i])
	{
		new = ft_lstnew(tab[i]);
		ft_lstadd_back(&ret, new);
		++i;
	}
	free(tab);
	return (ret);
}
*/


t_list	*sort_t_list(t_list *lst)
{
	t_list	*ret;
	t_list	*prev;
	t_list	*next;
	t_list	*first;

	if (!lst || !lst->next)
		return (NULL);	// but in this case the list is sorted...

	ret = ft_lstdup(lst);
	first = ret;
	prev = ret;
	while (ret && ret->next)
	{
		next = ret->next;
		if (ft_strcmp(ret->content, next->content) > 0)
		{
			ret->next = next->next;
			next->next = ret;
			if (ret == first)
			{
				first = next;
				prev = first;
			}
			else
				prev->next = next;
			ret = first;
		}
		else
		{
			prev = ret;
			ret = ret->next;
			next = ret->next;
		}
	}
	return (first);
}

int	print_envs(t_list *env, int fd)
{
	t_list	*tmp;
	char	*key;
	char	*value;

	if (!env)
		return (0);	// do we print an empty line? no i think we just move on to the next one
	tmp = sort_t_list(env);
	if (!tmp)
		tmp = env;
	value = NULL;
	while (tmp)
	{	// decide how to handle this...
		key = get_key(tmp->content);
		if (!key)
			return (1);
		ft_putstr_fd("declare -x ", fd);	// double check that this is the right message on Linux too.
		ft_putstr_fd(key, fd);
		if (ft_strlen(tmp->content) > ft_strlen(key))
		{
			ft_putstr_fd("=\"", fd);
			value = ft_substr(tmp->content, ft_strlen(key) + 1, ft_strlen(tmp->content) - ft_strlen(key) - 1);
			ft_putstr_fd(value, fd);		// in theory this works for when env var is empty
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);

		free(key);
		ft_scott_free(&value, 1);
		tmp = tmp->next;
	}
	ft_lstclear(&tmp, free);
	return (0);
}

// do i want to check if the Env Var already exists?
// Are the returns correct


int	ft_export(char	**args, t_list *env, int fd)
{
	int	ret;
	int	i;
	
	ret = 0;
	if (!args[1])
		return (print_envs(env, fd));
	else
	{
		i = 0;
		while (args[++i])
		{
			if (!check_valid_env(args[i]))
			{
				ret = 1;
				ft_putstr_fd("Error: Export not a valid identifier\n", 2);		// 2 or fd?
				continue ;
			}
			if (!replace_env(env, args[i]))
			{
				if (!add_env_elem(args[i], env))	// love the redundancy
					ret = 1;
			}
		}
	}
//	printf("ret: %d\n", ret);
	return (ret);
}
