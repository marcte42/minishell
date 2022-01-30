/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:36:47 by me                #+#    #+#             */
/*   Updated: 2022/01/30 20:37:59 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freestrtab(char **tab)
{
	int		i;
	
	if (!tab || !*tab)
		return ;
	i = -1;
	while (tab[++i])
		free(&tab[i]);
	free(tab);
}

void	free_sys(t_sys *mini)
{
	t_list	*cmds;
	t_list	*tmp;
	t_cmd	*cmd;
	
	ft_lstclear(&mini->env, free);
	cmds = mini->cmds;
	while (cmds)
	{
		cmd = cmds->content;
		if (cmd->raw)
			free(cmd->raw);
		ft_freestrtab(cmd->argv);
		free(cmd->clean);
		ft_lstclear(&cmd->r_in, free);
		ft_lstclear(&cmd->r_in, free);
		tmp = cmds->next;
		free(cmds);
		cmds = tmp;
	}
	if (mini->pfds)
		free(mini->pfds);
}
