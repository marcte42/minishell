/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:36:37 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/09 23:27:53 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_list *cmds)
{
	t_cmd	*cmd;

	signal(SIGINT, signal_handler_2);
	signal(SIGQUIT, SIG_IGN);
	while (cmds)
	{
		cmd = cmds->content;
		if (cmd->pid != 0)
		{
			if (waitpid(cmd->pid, &cmd->retval, 0) == -1)
				perror(NULL);
			if (WIFEXITED(cmd->retval))
				cmd->retval = WEXITSTATUS(cmd->retval);
			else if (WIFSIGNALED(cmd->retval))
				cmd->retval = WTERMSIG(cmd->retval) + 128;
		}
		cmds = cmds->next;
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	child_redirects(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
	return (0);
}

void	exec_path(t_sys *mini, char **clean)
{
	char	**paths;
	char	*env;
	char	*path_to_bin;
	char	*tmp;
	int		i;

	if (is_binary(clean[0]))
		execve(clean[0], clean, env_to_tab(mini->env));
	env = ft_getenv(mini, "PATH", mini->env);
	paths = ft_split(env, ':');
	ft_scott_free(&env, 0);
	if (!paths)
		return ;
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path_to_bin = ft_strjoin(tmp, clean[0]);
		ft_scott_free(&tmp, 0);
		if (is_binary(path_to_bin))
			execve(path_to_bin, clean, env_to_tab(mini->env));
		ft_scott_free(&path_to_bin, 0);
	}
	ft_free_strtab(paths);
	free(paths);
}

int	exec_child(t_sys *mini, t_cmd *cmd)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_redirects(cmd);
		close_pfds(mini);
		if (!cmd->clean)
			exit (1);
		exec_path(mini, cmd->clean);
		ft_putstr_fd(cmd->clean[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	return (SUCCESS);
}

int	exec(t_sys *mini)
{
	t_list	*cmds;
	t_cmd	*cmd;

	if (mini->cmds_count > 1 && !init_pfds(mini))
		return (ERROR);
	cmds = mini->cmds;
	while (cmds)
	{
		cmd = cmds->content;
		cmd->fd_in = get_fd_in(mini, cmd);
		cmd->fd_out = get_fd_out(mini, cmd);
		if (cmd->fd_in == -1 || cmd->fd_out == -1)
			cmd->retval = 1;
		else if (!cmd->clean[0] || is_builtin(cmd->clean[0]))
			cmd->retval = exec_builtin(mini, cmd);
		else
			exec_child(mini, cmd);
		cmds = cmds->next;
	}
	close_pfds(mini);
	ft_wait(mini->cmds);
	cmd = ft_lstlast(mini->cmds)->content;
	return (cmd->retval);
}
