/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:33:50 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/10/17 16:00:12 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmds(t_list *cmds)
{
	t_cmd	*cmd;
	char	**tab;
	int		i;
	
	while (cmds)
	{
		cmd = cmds->content;
		tab = cmd->argv;
		i = -1;
		while (tab[++i])
			printf("%s\t|\t", tab[i]);
		printf("\n");
		cmds = cmds->next;
	}
}

void	free_cmds(t_list *cmds)
{
	t_list	*tmp;
	t_cmd	*cmd;
	int		i;

	while (cmds)
	{
		tmp = cmds;
		cmd = (t_cmd *)cmds->content;
		i = -1;
		while(cmd->argv[++i])
			free(cmd->argv[i]);
		free(cmd->argv);
		free(cmd->raw);
		free(cmd);
		cmds = cmds->next;
		free(tmp);
	}
}

void	free_env(t_list *env)
{
	t_list	*tmp;

	while (env && env->next)
	{
		tmp = env;
		free(env->content);
		env = env->next;
		free(tmp);
	}
	free(env->content);
	free(env);
}

void	free_sys(t_sys *mini)
{
	free_env(mini->env);
	free(mini);
}
