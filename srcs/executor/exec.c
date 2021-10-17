/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:36:37 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/10/17 15:53:29 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**process_redirects(char **argv, int *fds, int k)
{
	char	**argv_clean;
	int		cleanidx = 0;
	int		fd;
	int		i;
	char	*buffer;

	i = 0;
	while (argv[i])
		i++;
	argv_clean = malloc((i + 1) * sizeof(char *));
	for (int j = 0; argv[j]; j++)
	{
		if (!strcmp(argv[j], "<"))
		{
			++j;
			fd = open(argv[j], O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			continue ;
		}
		if (!strcmp(argv[j], "<<"))
		{
			++j;
			while (1)
			{
				buffer = readline("> ");
				if (!strcmp(buffer, argv[j]))
					break ;
				write(fds[k + 1], buffer, strlen(buffer));
				write(fds[k + 1], "\n", 1);
			}
			continue ;
		}
		if (!strcmp(argv[j], ">"))
		{
			++j;
			fd = open(argv[j], O_CREAT | O_RDWR, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			continue ;
		}
		if (!strcmp(argv[j], ">>"))
		{
			++j;
			fd = open(argv[j], O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			continue ;
		}
		argv_clean[cleanidx++] = trim_quotes(argv[j]);
	}
	argv_clean[cleanidx] = NULL;
	return (argv_clean);
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
	exit (1);
}

void	process_pipes(t_list *cmds, int *fds, int j)
{
	if (cmds->next)
		dup2(fds[j + 3], STDOUT_FILENO);
    dup2(fds[j], STDIN_FILENO);
}

void	exec_cmds(t_list *cmds, int *fds, int pipes_count, t_sys *mini)
{
	t_cmd	*cmd;
	int		pid;
	int		j;
	int		i;
	char	**argv_clean;

	j = 0;
	while (cmds)
	{
		cmd = cmds->content;
		argv_clean = process_redirects(cmd->argv, fds, j);
		pid = fork();
		if (pid == 0)
		{
			
			process_pipes(cmds, fds, j);
			i = -1;
			while (++i < 2 * pipes_count)
				close(fds[i]);
			if (!argv_clean)
				exit (1);
			/*if (is_builtin(cmd->argv[0]))
				exec_builtin(argv_clean, mini->env, mini);*/
			else
				exec_path(argv_clean, mini);
		}
		free(argv_clean);
		cmds = cmds->next;
		j += 2;
	}
}

int	exec(t_list *cmds, t_sys *mini)
{
	int		*fds;
	int		pipes_count;
	int		i;
	int		status;

	pipes_count = ft_lstsize(cmds);
	fds = malloc(2 * pipes_count * sizeof(int));
	i = -1;
	while (++i < pipes_count)
		pipe(&fds[i * 2]);
	exec_cmds(cmds, fds, pipes_count, mini);
	i = -1;
	while (++i < 2 * pipes_count)
		close(fds[i]);
	i = -1;
	while (++i < pipes_count + 1)
		wait(&status);
	free(fds);
	return (status);
}
