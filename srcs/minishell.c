/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:55:02 by pravry            #+#    #+#             */
/*   Updated: 2021/10/17 16:01:04 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char *env[])
{
	char	*line;
	t_list	*env_lst;
	t_sys	*mini;

	env_lst = init_env(env);
	mini = init_sys(env_lst);
	line = NULL;
	if (ac != 1 || av[0][1] == '1')
		return (0);
	while (1)
	{
		line = readline("$> ");
		add_history(line);
		mini->cmds = parse(line);
		exec(mini->cmds, mini);
		free_cmds(mini->cmds);
	}
	free_sys(mini);
	return (0);
}
