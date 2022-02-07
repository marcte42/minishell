/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 03:36:19 by me                #+#    #+#             */
/*   Updated: 2022/02/07 03:36:21 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	unset_one_elem(char *arg, t_list **env)
{
	t_list	*elem;
	t_list	*tmp;

	elem = *env;
	if (elem && ft_strncmp(arg, elem->content, value_size(elem->content)) == 0)
	{
		elem = (*env)->next;
		free_elem(*env);
		*env = elem;
		return (0);
	}
	while (elem && elem->next)
	{
		if (ft_strncmp(arg, elem->next->content, \
			value_size(elem->next->content)) == 0)
		{
			tmp = elem->next->next;
			free_elem(elem->next);
			elem->next = tmp;
			return (0);
		}
		elem = elem->next;
	}
	return (0);
}

int	ft_unset(char **args, t_list **env)
{
	int		i;

	if (!args[1])
		return (0);
	i = 0;
	while (args[++i])
		unset_one_elem(args[i], env);
	return (0);
}
