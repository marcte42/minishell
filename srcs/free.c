/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:36:47 by me                #+#    #+#             */
/*   Updated: 2022/02/01 19:46:01 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unlink(void *file)
{
	t_rdr	*rdr;

	rdr = file;
	if (rdr->type == 2)
		unlink(rdr->file);
}

void	ft_lstcmd(t_list *lst,  void (*cmd)(void *))
{
	while (lst)
	{
		(*cmd)(lst->content);
		lst = lst->next;
	}
}

void	free_sys(t_sys *mini)
{
	t_list	*tmp;
	t_cmd	*cmd;
	int		i;
	
	tmp = mini->cmds;
	while (tmp)
	{
		cmd = tmp->content;
		ft_lstcmd(cmd->r_in, ft_unlink);
		if (cmd->raw)
			free(cmd->raw);
		i = -1;
		while (cmd->argv[++i])
			free(cmd->argv[i]);
		free(cmd->argv);
		free(cmd->clean);
		
		ft_lstclear(&cmd->r_in, free);
		ft_lstclear(&cmd->r_out, free);
		tmp = tmp->next;
	}
	ft_lstclear(&mini->cmds, free);
	free(mini->cmds);
	if (mini->pfds)
	{
		free(mini->pfds);
		mini->pfds = NULL;
	}
}

void	reset_free_sys(t_sys *mini)
{
	t_list	*tmp;
	t_cmd	*cmd;
	int		i;
	
	//ft_lstclear(&mini->env, free);
	tmp = mini->cmds;
	while (tmp)
	{
		cmd = tmp->content;
		if (cmd->raw)
			free(cmd->raw);
		i = -1;
		while (cmd->argv[++i])
			free(cmd->argv[i]);
		free(cmd->argv);
		free(cmd->clean);
		ft_lstclear(&cmd->r_in, free);
		ft_lstclear(&cmd->r_out, free);
		tmp = tmp->next;
	}
	ft_lstclear(&mini->cmds, free);
	free(mini->cmds);
	if (mini->pfds)
		free(mini->pfds);
}
