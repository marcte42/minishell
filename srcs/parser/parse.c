/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/10/25 16:14:02 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		free(raw_space);
		cmds = cmds->next;
	}
	return (1);
}

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
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		bzero(cmd, sizeof(t_cmd));
		cmd->raw = tokens[i];
		node = ft_lstnew(cmd);
		if (!node)
			return (NULL);
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

int	process_redirects_cmd(t_cmd *cmd)
{
	int		i;
	int		j;
	t_rdr	*rdr;

	j = 0;
	i = 0;
	while (cmd->argv[i])
		i++;
	cmd->clean = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (cmd->argv[++i])
	{
		if (!strcmp(cmd->argv[i], "<"))
		{
			i++;
			rdr = malloc(sizeof(rdr));
			rdr->type = 1;
			rdr->file = cmd->argv[i];
			ft_lstadd_back(&cmd->r_in, ft_lstnew(rdr));
			continue ;
		}
		if (!strcmp(cmd->argv[i], "<<"))
		{
			i++;
			rdr = malloc(sizeof(rdr));
			rdr->type = 2;
			rdr->file = cmd->argv[i];
			ft_lstadd_back(&cmd->r_in, ft_lstnew(rdr));
			continue ;
		}
		if (!strcmp(cmd->argv[i], ">"))
		{
			i++;
			rdr = malloc(sizeof(rdr));
			rdr->type = 1;
			rdr->file = cmd->argv[i];
			ft_lstadd_back(&cmd->r_out, ft_lstnew(rdr));
			continue ;
		}
		if (!strcmp(cmd->argv[i], ">>"))
		{
			i++;
			rdr = malloc(sizeof(rdr));
			rdr->type = 2;
			rdr->file = cmd->argv[i];
			ft_lstadd_back(&cmd->r_out, ft_lstnew(rdr));
			continue ;
		}
		cmd->clean[j++] = cmd->argv[i];
	}
	cmd->clean[j] = NULL;
	return (1);
}

int	parse_redirects(t_list *cmds)
{
	t_cmd	*cmd;

	while (cmds)
	{
		cmd = cmds->content;
		process_redirects_cmd(cmd);
		cmds = cmds->next;
	}
	return (1);
}

t_list	*parse(char *line)
{
	t_list	*cmds;

	if (!line)
		return (NULL);
	if (!control_quotes(line))
		return (NULL);
	line = parse_env(line);
	cmds = parse_pipes(line);
	free(line);
	parse_args(cmds);
	parse_redirects(cmds);
	return (cmds);
}
