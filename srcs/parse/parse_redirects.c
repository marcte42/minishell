/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/27 18:12:09 by mterkhoy         ###   ########.fr       */
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

	argv[0] = parse_env(mini, argv[0], mini->env);
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

int	parse_not_redirect(t_sys *mini, t_cmd *cmd, int i, int *j)
{
	int		has_env;
	char	**tab;

	has_env = ft_has_valid_env(mini, cmd->argv[i], -1);
	cmd->argv[i] = parse_env(mini, cmd->argv[i], mini->env);
	if (has_env == 1)
	{
		tab = ft_split_constraint(cmd->argv[i], ' ', is_inquotes);
		if (!tab)
			return (0);
		free(cmd->argv[i]);
		cmd->argv[i] = concat_tab_strs(tab);
		ft_free_strtab(tab);
		free(tab);
	}
	if (cmd->argv[i] && cmd->argv[i][0] == '\0' && has_env == 2)
		return (0);
	cmd->clean[(*j)++] = cmd->argv[i];
	return (1);
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
		trim_quotes(cmd->argv[i]);
		parse_not_redirect(mini, cmd, i, &j);
	}
	cmd->clean[j] = NULL;
	return (SUCCESS);
}
