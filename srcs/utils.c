/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:33:50 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/10/17 16:00:12 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_list *cmds)
{
	t_cmd	*cmd;
	char	**tab;
	int		i;
	
	while (cmds)
	{
		cmd = cmds->content;
		tab = cmd->argv;
		i = -1;
		while (tab[++i])
			printf("%s\t|\t", tab[i]);
		printf("\n");
		cmds = cmds->next;
	}
}




