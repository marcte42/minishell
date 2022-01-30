/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:36:37 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/30 12:59:25 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_redirects(t_sys *mini, t_cmd *cmd)
{
	int		fd;
	t_list	*lst;
	t_rdr	*rdr;
	
	// On commence par rediriger quoi qu'il arrive dans les pipes
	if (cmd->id != 0)
		dup2(mini->pfds[(cmd->id - 1) * 2], STDIN_FILENO);
	if (cmd->id != mini->cmds_count - 1)
		dup2(mini->pfds[cmd->id * 2 + 1], STDOUT_FILENO);

	// Si on a des redirections entrantes ou sortantes alors on redirige les fd
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

void	exec_path(t_sys *mini, char **tokens)
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
}

int exec_child(t_sys *mini, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (ERROR);	// make sure correct return
	if (cmd->pid == 0)
	{
		child_redirects(mini, cmd);
		close_pfds(mini);
		if (!cmd->clean)
			exit (1);
		exec_path(mini, cmd->clean);
		write (1, "Command not found\n", 18);	// perror instead?
		exit(127);
	}
	return (SUCCESS);
}

int	exec(t_list *cmds, t_sys *mini)
{
	t_cmd	*cmd;
	int		i;

	if (!init_pfds(mini))
		return (ERROR);
	while (cmds)
	{
		cmd = cmds->content;
		if (is_builtin(cmd->clean[0]))
			exec_builtin(mini, cmd);
		else
			exec_child(mini, cmd);
		cmds = cmds->next;
	}
	close_pfds(mini);
	i = -1;
	while (++i < mini->cmds_count)
		wait(&mini->status);	//waitpid maybe? 
	return (mini->status);
}
