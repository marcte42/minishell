/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:36:37 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/11/03 13:32:53 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_redirects(t_list *cmds, t_cmd *cmd, int *fds, int j)
{
	int		fd;
	t_list	*lst;
	t_rdr	*rdr;
	char	*buffer;

	if (cmd->r_in)
	{
		lst = cmd->r_in;
		while (lst)
		{
			rdr = lst->content;
			if (rdr->type == 1)
				fd = open((char *)rdr->file, O_RDONLY);
			dup2(fd, fds[j * 2]);
			lst = lst->next;
		}
	}
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
		dup2(fd, STDOUT_FILENO);
	}
	dup2(fds[j * 2], STDIN_FILENO);
	if (cmds->next && !cmd->r_out)
		dup2(fds[(j * 2) + 3], STDOUT_FILENO);
}

void	exec_path(char **tokens, t_sys *mini)
{
	char	**paths;
	char	*path_to_bin;
	char	*tmp;
	int		i;

	if (open(tokens[0], O_RDONLY) > 0)
		execve(tokens[0], tokens, env_to_tab(mini->env));
	paths = ft_split(getenv("PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path_to_bin = ft_strjoin(tmp, tokens[0]);
		free(tmp);
		if (open(path_to_bin, O_RDONLY) > 0)
			execve(path_to_bin, tokens, env_to_tab(mini->env));
		free(path_to_bin);
	}
	write (1, "Command not found\n", 18);
	exit(127);
}

int	exec(t_list *cmds, t_sys *mini)
{
	int		*fds;
	int		cmds_count;
	t_cmd	*cmd;
	int		i;
	int		j;
	int		pid;
	int		status;

	cmds_count = ft_lstsize(cmds);
	fds = malloc(2 * cmds_count * sizeof(int));
	i = -1;
	while (++i < cmds_count)
		pipe(&fds[i * 2]);
	j = 0;
	while (cmds)
	{
		cmd = cmds->content;
		pid = fork();
		if (pid == 0)
		{
			process_redirects(cmds, cmd, fds, j);
			i = -1;
			while (++i < 2 * cmds_count)
				close(fds[i]);
			if (!cmd->clean)
				exit (1);
			/*if (is_builtin(cmd->argv[0]))
				exec_builtin(argv_clean, mini->env, mini);*/
			exec_path(cmd->clean, mini);
		}
		cmds = cmds->next;
		j++;
	}
	i = -1;
	while (++i < 2 * cmds_count)
		close(fds[i]);
	i = -1;
	while (++i < cmds_count)
		wait(&status);
	free(fds);
	return (status);
}
