/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:38:15 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/06 14:31:17 by mterkhoy         ###   ########.fr       */
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
	while (++i < mini->cmds_count - 1)
		if (pipe(&(mini->pfds[i * 2])) == -1)
			return (ERROR);
	return (SUCCESS);
}

int	is_valid_file(char *file)
{
    struct stat sb;

    if (access(file, F_OK | R_OK) == -1 || stat(file, &sb) == -1)
        return (0);
    if ((sb.st_mode & S_IFMT) == S_IFREG)
        return (1);
    return (0);
}