/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:36:47 by me                #+#    #+#             */
/*   Updated: 2022/01/28 16:47:54 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_rdr()


void	free_cmds(t_list **lst)
{
	t_list	*tmp;
	t_cmd	*cmd;

	while (*lst)
	{
		tmp = *lst->next;
		cmd = (t_cmd *)(*lst)->content;
        ft_free_strtab(cmd->argv);
        ft_scott_free(&raw, 1);
/*		while(cmd->argv[++i])
			free(cmd->argv[i]);
		free(cmd->argv);	// scott_free
		free(cmd->raw);
*/
		free(*lst);
    	free(cmd);
		lst = tmp;
	}
}

void	free_env(t_list *env)
{
	t_list	*tmp;

	while (env && env->next)
	{
		tmp = env;
		free(env->content);
		env = env->next;
		free(tmp);
	}
	free(env->content);
	free(env);
}

void	free_sys(t_sys *mini)
{
	free_env(mini->env);
	free(mini);
}

/*
void    free_all()
{




}
*/
