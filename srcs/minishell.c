/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:55:02 by pravry            #+#    #+#             */
/*   Updated: 2022/01/29 11:49:33 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler(int num)
{
	if (num == SIGINT)
		rl_redisplay();
	exit(0);
}

int	main(int ac, char **av, char *env[])
{
	char	*line;
	t_list	*env_lst;
	t_sys	*mini;

	signal(SIGINT, handler);	// sort out how to do sigaction instead
	env_lst = init_env(env);
	mini = init_sys(env_lst);
	if (!mini)
	{
		free_env(env_lst);
		return (1);		// something other than 1? An Error Msg?
	}
	// free env_list?
	line = NULL;
	if (ac != 1 || av[0][1] == '1')
		return (0);
	while (1)
	{
		line = readline("$> ");
		add_history(line);	// can if fail? if so free line
		mini->cmds = parse(line);	// i assume this shit needs to be seucred, like all of these function calls!
		exec(mini->cmds, mini);
		//free_cmds(mini->cmds);
	}
	free_sys(mini);
	return (0);
}
