/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:36:37 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/29 19:18:07 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_redirects(t_list *cmds, t_cmd *cmd, int *fds, int j)
{
	int		fd;
	t_list	*lst;
	t_rdr	*rdr;
	
	if (j != 0)
		dup2(fds[(j - 1) * 2], STDIN_FILENO);
	if (cmds->next)
		dup2(fds[j * 2 + 1], STDOUT_FILENO);
	if (cmd->r_in)
	{
		lst = cmd->r_in;
		while (lst)
		{
			// yea we could add more security checks here
			rdr = lst->content;
			fd = open((char *)rdr->file, O_RDONLY);
			dup2(fd, STDIN_FILENO); 
			lst = lst->next;
		}
	}
	if (cmd->r_out)
	{
		lst = cmd->r_out;
		while (lst)	// same as above, security checks i think
		{
			rdr = lst->content;
			if (rdr->type == 1)	// if rdr first
				fd = open((char *)rdr->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
				fd = open((char *)rdr->file, O_CREAT | O_RDWR | O_APPEND, 0644);
			// should we: if (fd == -1) return and free?
			lst = lst->next;
		}
		dup2(fd, STDOUT_FILENO); // can it fail? yes rets (-1) if fail, secure it
	}
	
}

void	exec_path(char **tokens, t_sys *mini)
{
	char	**paths;
	char	*path_to_bin;
	char	*tmp;
	int		i;

	// if (!tokens || !mini) ideally

	// secure all the split and joins

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
	write (1, "Command not found\n", 18);	// perror instead?
	exit(127);
}

int	exec(t_list *cmds, t_sys *mini)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	if (!init_pfds(mini))
		return (ERROR);
	j = 0;
	while (cmds)
	{
		cmd = cmds->content;
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (ERROR);	// make sure correct return
		if (cmd->pid == 0)
		{
			child_redirects(cmds, cmd, mini->pfds, j);
			close_pfds(mini);
			if (!cmd->clean)
				exit (1);
			exec_path(cmd->clean, mini); 
		}
		cmds = cmds->next;
		j++;
	}
	close_pfds(mini);
	i = -1;
	while (++i < mini->cmds_count)
		wait(&mini->status);	//waitpid maybe? 
	return (mini->status);
}
