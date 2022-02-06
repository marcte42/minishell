/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:40:38 by pravry            #+#    #+#             */
/*   Updated: 2022/01/30 16:41:23 by mterkhoy         ###   ########.fr       */
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
	while (*value != '=')
	{
		size++;
		value++;
	}
	return (size);
}

int	ft_unset(char **args, t_list *env)
{
	t_list	*tmp;

	if (!args[1])
		return (0);
	if (ft_strncmp(args[1], env->content, value_size(env->content)) == 0)
	{
		tmp = env->next;
		free_elem(env);
		env = tmp;
	}
	while (env && env->next)
	{
		if (ft_strncmp(args[1], env->next->content, \
			value_size(env->next->content)) == 0)
		{
			tmp = env->next->next;
			free_elem(env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}
