/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/29 13:05:15 by mterkhoy         ###   ########.fr       */
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
			// On doit aussi free toutes les nodes et tous les contents qui precedent
			free(tokens);
			return (ERROR);
		}
		cmd->raw = tokens[i];
		node = ft_lstnew(cmd);
		if (!node)
		{
			// On doit aussi free toutes les nodes et tous les contents qui precedent
			free(tokens);
			return (ERROR);
		}
		ft_lstadd_back(&lst, node);
	}
	free(tokens);
	return (lst);
}

void	print_list(t_list *cmds)
{
	t_cmd	*cmd;
	t_rdr	*rdr;
	int		i;

	while (cmds)
	{
		cmd = cmds->content;
		i = -1;
		while (cmd->clean[++i])
		{
			printf("%s\n", cmd->clean[i]);
		}
		while (cmd->r_in)
		{
			rdr = cmd->r_in->content;
			printf("%s %d -> \n", (char *) rdr->file, rdr->type);
			cmd->r_in = cmd->r_in->next;
		}
		cmds = cmds->next;
	}
}

int handle_heredoc(t_rdr *rdr, char *argv)
{
	int		fd;
	char	*buffer;
	char	*heredoc_name;
	
	heredoc_name = ft_strjoin("/tmp/", argv);
	if (!heredoc_name)
		return (0);
	rdr->file = heredoc_name;
	fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (!fd)
		return (0);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || !ft_strcmp(buffer, argv))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
	}
	if (!buffer)
		write(1, "warning: here-document delimited by end-of-file\n", 48);
	close (fd);
	return (1);
}

int add_r_in(t_cmd *cmd, char *argv, int type)
{
	t_rdr	*rdr;
	t_list	*node;
	
	rdr = malloc(sizeof(rdr));
	if (!rdr)
		return (0);
	rdr->type = type;
	rdr->file = argv;
	if (type == 2)
	{
		if (!handle_heredoc(rdr, argv))
		{
			free (rdr);
			return (0);
		}
	}
	node = ft_lstnew(rdr);
	if (!node)
	{
		free(rdr);
		return (0);
	}
	ft_lstadd_back(&cmd->r_in, node);
	return (1);
}

int add_r_out(t_cmd *cmd, char *argv, int type)
{
	t_rdr	*rdr;
	t_list	*node;
	
	rdr = malloc(sizeof(rdr));
	if (!rdr)
		return (0);
	rdr->type = type;
	rdr->file = argv;
	node = ft_lstnew(rdr);
	if (!node)
	{
		free(rdr);
		return (0);
	}
	ft_lstadd_back(&cmd->r_out, node);
	return (1);
}

int add_redirect(t_cmd *cmd, char *argv, char *type_char)
{
	int		type;

	type = 1;
	if (!ft_strcmp(type_char, "<<") || !ft_strcmp(type_char, ">>"))
		type = 2;
	if (!ft_strcmp(type_char, "<") || !ft_strcmp(type_char, "<<"))
		return (add_r_in(cmd, argv, type));
	return (add_r_out(cmd, argv, type));
}

int	parse_redirects(t_cmd *cmd)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!cmd)
		return (0);
	while (cmd->argv[i])// i have a strtab_len(), if len 0 we return?
		i++;
	cmd->clean = malloc((i + 1) * sizeof(char *));// ft_calloc
	if (!cmd->clean)
		return (0);
	i = -1;
	while (cmd->argv[++i])
	{
		if (!ft_strcmp(cmd->argv[i], "<") || !ft_strcmp(cmd->argv[i], "<<")
			|| !ft_strcmp(cmd->argv[i], ">") || !ft_strcmp(cmd->argv[i], ">>"))
		{
			i++;
			if (!add_redirect(cmd, cmd->argv[i], cmd->argv[i - 1]))
				return (0);
			continue ;
		}
		cmd->clean[j++] = cmd->argv[i];
	}
	cmd->clean[j] = NULL;
	return (1);
}

int	parse_args(t_list *cmds)
{
	t_cmd	*cmd;
	char	*raw_space;

	while (cmds)
	{
		cmd = cmds->content;
		raw_space = add_space(cmd->raw);
		if (!raw_space)
			return (0);
		cmd->argv = ft_split_constraint(raw_space, ' ', is_inquotes);
		parse_redirects(cmd);
		free(raw_space);
		cmds = cmds->next;
	}
	return (SUCCESS);
}

int parse(char *line, t_sys *mini)
{
	if (!line)
		return (ERROR);
	if (!control_quotes(line))
		return (ERROR);
	line = parse_env(line, mini->env);
	if(!line)
		return (ERROR);
	mini->cmds = parse_pipes(line);
	if (!mini->cmds)
		return (ERROR);
	parse_args(mini->cmds);
	return (SUCCESS);
}
