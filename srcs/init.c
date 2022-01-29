/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:36:47 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/29 13:07:57 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	init_sys(t_sys *mini, t_list *env)
{
	mini->env = env;
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
