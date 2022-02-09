/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/09 13:45:19 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_heredoc_file(char **argv, int id, int *fd)
{
	char	*name;
	char	*index;
	char	*heredoc_name;

	index = ft_itoa(id);
	if (!index)
		return (NULL);
	name = ft_strjoin(*argv, index);
	free(index);
	if (!name)
		return (NULL);
	heredoc_name = ft_strjoin("/tmp/", name);
	free(name);
	if (!heredoc_name)
		return (NULL);
	*fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd == -1)
	{
		free(heredoc_name);
		return (NULL);
	}
	return (heredoc_name);
}

int	write_to_heredoc(t_sys *mini, int fd, char *argv, int quote)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("> ");
		if (!buffer || !ft_strcmp(buffer, argv))
			break ;
		if (buffer && !quote)
			buffer = parse_env_heredoc(mini, buffer, mini->env);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	if (!buffer)
		ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
	else
		free(buffer);
}

int	handle_heredoc(t_sys *mini, t_rdr *rdr, char **argv, int id)
{
	int		fd;
	char	*heredoc_name;
	int		quote;

	heredoc_name = make_heredoc_file(argv, id, &fd);
	if (!heredoc_name)
		return (ERROR);
	quote = has_quotes(*argv);
	trim_quotes(*argv);
	write_to_heredoc(mini, fd, *argv, quote);
	free(*argv);
	*argv = heredoc_name;
	rdr->file = heredoc_name;
	close (fd);
	return (SUCCESS);
}

int	parse_args(t_sys *mini, t_list *cmds)
{
	t_cmd	*cmd;
	char	*raw_space;
	int		i;

	i = 0;
	while (cmds)
	{
		cmd = cmds->content;
		cmd->id = i++;
		raw_space = add_space(cmd->raw);
		if (!raw_space)
			return (ERROR);
		cmd->argv = ft_split_constraint(raw_space, ' ', is_inquotes);
		free(raw_space);
		if (!parse_redirects(mini, cmd, 0, 0))
			return (ERROR);
		cmds = cmds->next;
	}
	return (SUCCESS);
}

int	parse(t_sys *mini)
{
	if (!control_quotes(mini->line))
	{
		ft_putstr("minishell: syntax error\n");
		return (ERROR);
	}
	if (!mini->line)
		return (ERROR);
	mini->cmds = parse_pipes(mini->line);
	if (!mini->cmds)
		return (ERROR);
	if (!parse_args(mini, mini->cmds))
		return (ERROR);
	mini->cmds_count = ft_lstsize(mini->cmds);
	return (SUCCESS);
}
