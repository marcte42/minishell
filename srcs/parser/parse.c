/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/10/17 16:02:05 by mterkhoy         ###   ########.fr       */
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

t_list	*parse(char *line)
{
	t_list	*cmds;

	if (!control_quotes(line))
		return (NULL);
	line = parse_env(line);
	if (!line)
		return (NULL);
	cmds = parse_pipes(line);
	free(line);
	parse_args(cmds);
	return (cmds);
}
