/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:38:24 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/06 16:27:28 by mterkhoy         ###   ########.fr       */
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
		if (ft_strcmp(builtin[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtin(t_sys *mini, t_cmd *cmd)
{
	int		fd;

	fd = cmd->fd_out;
	if (!cmd->clean[0])
		return (SUCCESS);
	if (!ft_strcmp(cmd->clean[0], "echo"))
		return (ft_echo(cmd->clean, fd));
	else if (!ft_strcmp(cmd->clean[0], "cd"))
		return (ft_cd(mini, cmd->clean));
	else if (!ft_strcmp(cmd->clean[0], "pwd"))
		return (ft_pwd(fd));
	else if (!ft_strcmp(cmd->clean[0], "env"))
		return (ft_env(mini, fd));
	else if (!ft_strcmp(cmd->clean[0], "export"))
		return (ft_export(cmd->clean, mini->env, fd));
	else if (!ft_strcmp(cmd->clean[0], "unset"))
		return (ft_unset(cmd->clean, mini->env));
	else if (!ft_strcmp(cmd->clean[0], "exit"))
		return (ft_exit(cmd->clean, mini));
	return (SUCCESS);
}
