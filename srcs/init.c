/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:36:47 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/10/17 13:19:03 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_sys 	*init_sys(t_list *env)
{
	t_sys	*mini;

	mini = malloc(sizeof(t_sys));
	mini->ret = 0;
	mini->exit = 0;
	mini->cmds = NULL;
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
		if (!node)
			return (NULL);
		ft_lstadd_back(&lst, node);
	}
	return (lst);
}
