/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/08 21:22:15 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parse_pipes(char *line)
{
	t_list	*lst;
	t_list	*node;
	char	**tokens;
	t_cmd	*cmd;
	int		i;

	lst = NULL;
	tokens = ft_split_constraint(line, '|', is_inquotes);
	if (!tokens)
		return (ERROR);
	i = -1;
	while (tokens[++i])
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
		{
			ft_lstclear(&lst, free);
			free(tokens);
			return (ERROR);
		}
		cmd->raw = tokens[i];
		node = ft_lstnew(cmd);
		if (!node)
		{
			ft_lstclear(&lst, free);
			free(tokens);
			return (ERROR);
		}
		ft_lstadd_back(&lst, node);
	}
	free(tokens);
	return (lst);
}

int	handle_heredoc(t_sys *mini, t_rdr *rdr, char **argv, int id)
{
	int		fd;
	char	*buffer;
	char	*heredoc_name;
	char	*name;
	char	*index;
	int		quote;

	index = ft_itoa(id);
	name = ft_strjoin(*argv, index);
	free(index);
	heredoc_name = ft_strjoin("/tmp/", name);
	free(name);
	if (!heredoc_name)
		return (ERROR);
	quote = has_quotes(*argv);
	trim_quotes(*argv);
	fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (!fd)
		return (ERROR);
//	signal(SIGINT, signal_handler_heredoc);
//	signal(SIGQUIT, signal_handler_heredoc);
	while (1)
	{
		buffer = readline("> ");
		if (buffer && !quote)
			buffer = parse_env_heredoc(mini, buffer, mini->env);
		if (!buffer || !ft_strcmp(buffer, *argv))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
//	signal(SIGINT, signal_handler);
//	signal(SIGQUIT, SIG_IGN);
	free(*argv);
	*argv = heredoc_name;
	rdr->file = heredoc_name;
	if (!buffer)
		ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
	else
		free(buffer);
	close (fd);
	return (SUCCESS);
}

int	add_r_in(t_sys *mini, t_cmd *cmd, char **argv, int type)
{
	t_rdr	*rdr;
	t_list	*node;

	rdr = malloc(sizeof(t_rdr));
	if (!rdr)
		return (ERROR);
	rdr->type = type;
	rdr->file = *argv;
	if (type == 2)
	{
		if (!handle_heredoc(mini, rdr, argv, cmd->id))
		{
			free (rdr);
			return (ERROR);
		}
	}
	node = ft_lstnew(rdr);
	if (!node)
	{
		free(rdr);
		return (ERROR);
	}
	ft_lstadd_back(&cmd->r_in, node);
	return (SUCCESS);
}

int	add_r_out(t_cmd *cmd, char **argv, int type)
{
	t_rdr	*rdr;
	t_list	*node;

	rdr = malloc(sizeof(t_rdr));
	if (!rdr)
		return (0);
	rdr->type = type;
	rdr->file = *argv;
	node = ft_lstnew(rdr);
	if (!node)
	{
		free(rdr);
		return (ERROR);
	}
	ft_lstadd_back(&cmd->r_out, node);
	return (SUCCESS);
}

int	add_redirect(t_sys *mini, t_cmd *cmd, char **argv, char *type_char)
{
	int		type;

	if (!*argv || !ft_strcmp(*argv, "<") || !ft_strcmp(*argv, "<<")
			|| !ft_strcmp(*argv, ">") || !ft_strcmp(*argv, ">>")
			|| !ft_strcmp(*argv, "|"))
	{
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		return (ERROR);
	}
	type = 1;
	if (!ft_strcmp(type_char, "<<") || !ft_strcmp(type_char, ">>"))
		type = 2;
	if (!ft_strcmp(type_char, "<") || !ft_strcmp(type_char, "<<"))
		return (add_r_in(mini, cmd, argv, type));
	return (add_r_out(cmd, argv, type));
}

int	parse_redirects(t_sys *mini, t_cmd *cmd)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!cmd)
		return (0);
	while (cmd->argv[i])
		i++;
	cmd->clean = malloc((i + 1) * sizeof(char *));
	if (!cmd->clean)
		return (0);
	i = -1;
	while (cmd->argv[++i])
	{
		if (!ft_strcmp(cmd->argv[i], "<") || !ft_strcmp(cmd->argv[i], "<<")
			|| !ft_strcmp(cmd->argv[i], ">") || !ft_strcmp(cmd->argv[i], ">>"))
		{
			i++;
			if (!add_redirect(mini, cmd, &cmd->argv[i], cmd->argv[i - 1]))
				return (ERROR);
			continue ;
		}
		trim_quotes(cmd->argv[i]);
		cmd->clean[j++] = cmd->argv[i];
	}
	cmd->clean[j] = NULL;
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
		if (!parse_redirects(mini, cmd))
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
	mini->line = parse_env(mini, mini->line, mini->env);
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
