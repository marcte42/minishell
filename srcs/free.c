/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:36:47 by me                #+#    #+#             */
/*   Updated: 2022/02/06 17:06:06 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_error(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
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
	free(mini->line);
	mini->cmds_count = 0;
	mini->exit = 0;
}