/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:36:47 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/10/25 12:28:14 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sys 	*init_sys(t_list *env)
{
	t_sys	*mini;

	mini = malloc(sizeof(t_sys));	// i could make it memalloc?
	ft_bzero(mini, sizeof(t_sys));
	mini->env = env;
	return (mini);
}

t_list	*init_env(char **env)
{
	t_list	*lst;
	t_list	*node;
	char	*env_value;
	int		i;

	lst = NULL;
	i = -1;
	while (env[++i])
	{
		env_value = ft_strdup(env[i]);
		if (!env_value)
			return (NULL);
		node = ft_lstnew(env_value);
		if (!node)	// free env_value
			return (NULL);
		ft_lstadd_back(&lst, node);
	}
	return (lst);
}
