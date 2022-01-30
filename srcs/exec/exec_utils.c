/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:38:15 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/30 20:12:18 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pfds(t_sys *mini)
{
	int	i;

	i = -1;
	while (++i < 2 * (mini->cmds_count - 1))
		close(mini->pfds[i]);// does close work on fd = -1? in error case
	return (SUCCESS);
}

int	init_pfds(t_sys *mini)
{
	int	i;

	mini->pfds = malloc(2 * (mini->cmds_count - 1) * sizeof(int));
	if (!mini->pfds)
		return (ERROR);
	i = -1;
	while (++i < mini->cmds_count)
		if (pipe(&mini->pfds[i * 2]) == -1)
			return (ERROR);
	return (SUCCESS);
}
