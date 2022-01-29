/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/29 11:56:30 by mterkhoy         ###   ########.fr       */
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
		return (NULL);
	i = -1;
	while (tokens[++i])
	{	// maybe just make a free_cmd() and call each time, there is one, but fix it
		cmd = malloc(sizeof(t_cmd));	// calloc so no bzero
		if (!cmd)	// ft_free_strtab(tokens); and free lst
			return (NULL);
		bzero(cmd, sizeof(t_cmd));
		cmd->raw = tokens[i];
		node = ft_lstnew(cmd);
		if (!node)	// free cmds and lst and tokens
			return (NULL);
		ft_lstadd_back(&lst, node);
	}
	free(tokens);	// ok so you free the table of strings but not
					// the strings? i think
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
		if (!raw_space)	// free cmds but not in this func
			return (0);
		// what happens if split fails, things to free? ret(0)?
		cmd->argv = ft_split_constraint(raw_space, ' ', is_inquotes);
		parse_redirects(cmd);
		free(raw_space);
		cmds = cmds->next;
	}
	return (1);
}

t_list	*parse(char *line)
{
	t_list	*cmds;

	//surely some more checks... like for all the func calls

	if (!line)
		return (NULL);
	if (!control_quotes(line))
		return (NULL);
	line = parse_env(line);
	cmds = parse_pipes(line);
	parse_args(cmds);
	return (cmds);
}
