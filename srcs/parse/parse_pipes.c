/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/09 20:45:04 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_to_cmd_list(t_list **lst, char **tokens)
{
	t_cmd	*cmd;
	t_list	*node;
	int		i;

	i = -1;
	while (tokens[++i])
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
		{
			ft_lstclear(lst, free);
			free(tokens);
			return (ERROR);
		}
		cmd->raw = tokens[i];
		node = ft_lstnew(cmd);
		if (!node)
		{
			ft_lstclear(lst, free);
			free(tokens);
			return (ERROR);
		}
		ft_lstadd_back(lst, node);
	}
	return (SUCCESS);
}

t_list	*parse_pipes(char *line)
{
	t_list	*lst;
	char	**tokens;

	lst = NULL;
	tokens = ft_split_constraint(line, '|', is_inquotes);
	if (!tokens)
		return (NULL);
	if (!tab_to_cmd_list(&lst, tokens))
	{
		free(tokens);
		return (NULL);
	}
	free(tokens);
	return (lst);
}
