/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:38:15 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/06 21:04:10 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pfds(t_sys *mini)
{
	int	i;

	i = -1;
	while (++i < 2 * (mini->cmds_count - 1))
		close(mini->pfds[i]);
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

int	is_binary(char *file)
{
	struct stat	sb;

	if (access(file, F_OK | X_OK) == -1 || stat(file, &sb) == -1)
		return (0);
	if ((sb.st_mode & S_IFMT) == S_IFREG)
		return (1);
	return (0);
}

int	get_fd_in(t_sys *mini, t_cmd *cmd)
{
	int		fd;
	t_list	*lst;
	t_rdr	*rdr;

	fd = STDIN_FILENO;
	if (cmd->id != 0)
		fd = mini->pfds[(cmd->id - 1) * 2];
	lst = cmd->r_in;
	while (lst)
	{
		if (fd > 2)
			close(fd);
		rdr = lst->content;
		fd = open((char *)rdr->file, O_RDONLY);
		if (fd == -1)
		{
			minishell_error(rdr->file);
			return (fd);
		}
		lst = lst->next;
	}
	return (fd);
}

int	get_fd_out(t_sys *mini, t_cmd *cmd)
{
	int		fd;
	t_list	*lst;
	t_rdr	*rdr;

	fd = STDOUT_FILENO;
	if (cmd->id != mini->cmds_count - 1)
		fd = mini->pfds[cmd->id * 2 + 1];
	lst = cmd->r_out;
	while (lst)
	{
		if (fd > 2)
			close(fd);
		rdr = lst->content;
		if (rdr->type == 1)
			fd = open((char *)rdr->file, O_CREAT | O_WRONLY, 0600);
		else
			fd = open((char *)rdr->file, O_CREAT | O_WRONLY
					| O_APPEND, 0600);
		if (fd == -1)
			return (special_mini_error(rdr->file, fd));
		lst = lst->next;
	}
	return (fd);
}
