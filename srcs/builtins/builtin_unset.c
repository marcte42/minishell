/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:40:38 by pravry            #+#    #+#             */
/*   Updated: 2022/02/06 23:11:45 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//seems fine, but definitely test

void	free_elem(t_list *env)
{
	if (!env)
		return ;
	if (env->content)
		free(env->content);
	free(env);
}

int	value_size(char *value)
{
	int	size;

	size = 0;
	while (*value && *value != '=')
	{
		size++;
		value++;
	}
	return (size);
}

int	ft_unset(char **args, t_list *env)
{
	int		i;
	t_list	*tmp;
	t_list	*elem;

	i = 0;
	if (!args[1])
		return (0);
	while (args[++i])
	{
		elem = env;
	//	if (ft_strncmp(args[i], env->content, value_size(env->content)) == 0)
		if (ft_strncmp(args[i], elem->content, value_size(elem->content)) == 0)
		{
			elem = env->next;
			free_elem(env);
			env = elem;
			continue ;
		}
	//	while (env && env->next)
		while (elem && elem->next)
		{
//			if (ft_strncmp(args[i], env->next->content, \
//				value_size(env->next->content)) == 0)
			if (ft_strncmp(args[i], elem->next->content, \
				value_size(elem->next->content)) == 0)
			{
				tmp = elem->next->next;
				free_elem(elem->next);
				elem->next = tmp;
				continue ;
			//	return (0);
/*
				tmp = env->next->next;
				free_elem(env->next);
				env->next = tmp;
				continue ;
			//	return (0);
*/
			}
			//env = env->next;
			elem = elem->next;
		}
	}
	return (0);
}
