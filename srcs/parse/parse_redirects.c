/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/11 02:06:02 by me               ###   ########.fr       */
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

	// maybe we need to check expansions here!
	// something like
//	char	*tmp;

	// redundant but at least it works.
	argv[0] = parse_env(mini, argv[0], mini->env);

/*	if (!tmp || !ft_strcmp(tmp, "<") || !ft_strcmp(tmp, "<<")
		|| !ft_strcmp(tmp, ">") || !ft_strcmp(tmp, ">>")
		|| !ft_strcmp(tmp, "|"))
		return (ERROR);
*/
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


// adding * to *cmd didn't help, why doesn't it work...
int	parse_not_redirect(t_sys *mini, t_cmd **cmd, int *i, int *j)
{
	int	has_env;

	has_env = ft_has_valid_env(mini, (*cmd)->argv[*i]);
	(*cmd)->argv[*i] = parse_env(mini, (*cmd)->argv[*i], mini->env);
	trim_quotes((*cmd)->argv[*i]);
		// here, if it was an env var type, but not defined, we don't increment j
		// need to skip only if empty thing was a env var, if '' you keep it...
	if ((*cmd)->argv[*i][0] == '\0' && has_env == 2)	// ok i think this works...		
		return (0);
	// maybe something like if (has_env == 1 )
	// if argv[i] an env var we need to trim all but 1 space before, after and in between words.
	// oh and to make it harder, we only trim if env var not between quotes...
		// i guess we need this further up, above trim quotes...
	(*cmd)->clean[*j] = (*cmd)->argv[*i];
		// yea what we want is if an env vard doesn't exist, we don't add to clean
	++(*j);
	return (1);
}

int	parse_redirects(t_sys *mini, t_cmd *cmd, int i, int j)
{
	if (!cmd)
		return (0);
	i = strtab_len(cmd->argv);
	// change to calloc?
	cmd->clean = malloc((i + 1) * sizeof(char *));
	if (!cmd->clean)
		return (0);

// testing

/*	i = -1;
	while (cmd->argv[++i])
	{
		printf("%s\n %d\n", cmd->argv[i], ft_has_valid_env(mini, cmd->argv[i]));
	}
*/


	i = -1;
	while (cmd->argv[++i])
	{
		if (!ft_strcmp(cmd->argv[i], "<") || !ft_strcmp(cmd->argv[i], "<<")
			|| !ft_strcmp(cmd->argv[i], ">") || !ft_strcmp(cmd->argv[i], ">>"))
		{
			i++;
			// but maybe need to check expansions here?
			if (!add_redirect(mini, cmd, &cmd->argv[i], cmd->argv[i - 1]))
				return (ERROR);
			continue ;
		}
		parse_not_redirect(mini, &cmd, &i, &j);
/*		cmd->argv[i] = parse_env(mini, cmd->argv[i], mini->env);
		trim_quotes(cmd->argv[i]);
		// maybe here, if (!cmd->argv not ++j?)
		// here, if it was an env var type, but not defined, we don't increment j
		// not quite this need to skip only if empty thing was a env var, if '' you keep it...
		if (cmd->argv[i][0] != '\0')	// ok i think this works...		
			cmd->clean[j++] = cmd->argv[i];
		// yea what we want is if an env vard doesn't exist, we don't add to clean
*/
	}
	cmd->clean[j] = NULL;
//	ft_print_strtab(cmd->clean);
	return (SUCCESS);
}
