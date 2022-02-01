/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:38:24 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/01 22:47:23 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	char	*builtin[] = {"pwd", "cd", "echo", "export", "unset", "exit", "env", NULL}; // pas a la norm :(
	int		i;

	i = 0;
	while (builtin[i])
	{
		if (strcmp(builtin[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	builtin_redirects(t_sys *mini, t_cmd *cmd)	// not sure i understand this function
{
	int		fd;
	t_list	*lst;
	t_rdr	*rdr;

	fd = STDOUT_FILENO;
	if (cmd->id != mini->cmds_count - 1)
		fd = mini->pfds[cmd->id * 2 + 1];
	if (cmd->r_out)
	{
		lst = cmd->r_out;
		while (lst)
		{
			rdr = lst->content;
			if (rdr->type == 1)
				fd = open((char *)rdr->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
				fd = open((char *)rdr->file, O_CREAT | O_RDWR | O_APPEND, 0644);
			lst = lst->next;
		}
	}
	return (fd);
}

int	exec_builtin(t_sys *mini, t_cmd *cmd)
{
	int		fd;

	fd = builtin_redirects(mini, cmd);
	if (!cmd->clean[0])
		return (SUCCESS);
	if (!strcmp(cmd->clean[0], "echo"))
		return (ft_echo(cmd->clean, fd));
	else if (!strcmp(cmd->clean[0], "cd"))
		return (ft_cd(mini, cmd->clean));
	else if (!strcmp(cmd->clean[0], "pwd"))
		return (ft_pwd(fd));
	else if (!strcmp(cmd->clean[0], "env"))
		return (ft_env(mini, fd));
	else if (!strcmp(cmd->clean[0], "export"))
		return (ft_export(cmd->clean, mini->env));
	else if (!strcmp(cmd->clean[0], "unset"))
		return (ft_unset(cmd->clean, mini->env));
	else if (!strcmp(cmd->clean[0], "exit"))
		return (ft_exit(cmd->clean, mini));
	return (SUCCESS);
}
