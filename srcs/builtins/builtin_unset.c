/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:40:38 by pravry            #+#    #+#             */
/*   Updated: 2021/06/28 12:18:18 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_elem(t_envi *env)
{
	free(env->value);
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

int	ft_unset(char **args, t_envi *env)
{
	t_envi	*tmp;

	if (!args[1])
		return (SUCCESS);
	if (ft_strncmp(args[1], env->value, value_size(env->value)) == 0)
	{
		tmp = env->next;
		free_elem(env);
		env = tmp;
	}
	while (env && env->next)
	{
		if (ft_strncmp(args[1], env->next->value, value_size(env->next->value)) == 0)
		{
				tmp = env->next->next;
				free_elem(env->next);
				env->next = tmp;
				return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}
