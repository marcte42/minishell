/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:36:47 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/31 17:02:06 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			ft_lstclear(&lst, free);
			return (ERROR);
		}
		node = ft_lstnew(env_value);
		if (!node)
		{
			free(env);
			ft_lstclear(&lst, free);
			return (ERROR);
		}
		ft_lstadd_back(&lst, node);
	}
	return (lst);
}

int		init_sys(t_sys *mini, char **env)
{
	ft_bzero(mini, sizeof(t_sys));
	mini->env = init_env(env);
	if (!mini->env)
		return (ERROR);
	return (SUCCESS);
}