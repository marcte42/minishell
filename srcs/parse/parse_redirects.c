/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/09 23:27:05 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (ERROR);
	type = 1;
	if (!ft_strcmp(type_char, "<<") || !ft_strcmp(type_char, ">>"))
		type = 2;
	if (!ft_strcmp(type_char, "<") || !ft_strcmp(type_char, "<<"))
		return (add_r_in(mini, cmd, argv, type));
	return (add_r_out(cmd, argv, type));
}

int	parse_redirects(t_sys *mini, t_cmd *cmd, int i, int j)
{
	if (!cmd)
		return (0);
	i = strtab_len(cmd->argv);
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
		cmd->argv[i] = parse_env(mini, cmd->argv[i], mini->env);
		trim_quotes(cmd->argv[i]);
		cmd->clean[j++] = cmd->argv[i];
	}
	cmd->clean[j] = NULL;
	return (SUCCESS);
}
