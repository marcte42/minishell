/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:33:50 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/08 23:39:57 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *path)
{
	int	fd;

	errno = 0;
	fd = open(path, O_WRONLY);
	if (errno == EISDIR)
		return (1);
	if (fd > 0)
		close(fd);
	return (0);
}

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
