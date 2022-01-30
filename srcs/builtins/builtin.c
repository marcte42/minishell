/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:38:24 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/01/30 12:52:32 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_builtin(char *cmd)
{
	char	*builtin[] = {"pwd", "cd", "echo", "export", "unset", "exit", "env", NULL};
	int		i;

	i = 0;
	while (builtin[i])
	{
		if (strcmp(builtin[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*void		ft_env(t_sys *mini)
{
	while (mini->env)
	{
		printf("%s\n", mini->env->content);
		mini->env = mini->env->next;
	}
}*/

int		exec_builtin(t_sys *mini, t_cmd *cmd)
{
	(void) mini;
	
	if (!strcmp(cmd->clean[0], "echo"))
		return (ft_echo(cmd->clean));
	/*else if (!strcmp(cmd->clean[0], "pwd"))
		ft_pwd();
	else if (!strcmp(cmd->clean[0], "cd"))
		ft_cd(cmd->clean, mini->env);
	else if (!strcmp(cmd->clean[0], "export"))
		ft_export(cmd->clean, mini->env);
	else if (!strcmp(cmd->clean[0], "unset"))
		ft_unset(cmd->clean, mini->env);
	else if (!strcmp(cmd->clean[0], "exit"))
		ft_exit(cmd->clean, mini);
	else if (!strcmp(cmd->clean[0], "env"))
		ft_env(mini);*/
	return (0);
}
