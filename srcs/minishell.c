/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:55:02 by pravry            #+#    #+#             */
/*   Updated: 2022/01/29 13:24:08 by mterkhoy         ###   ########.fr       */
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
	t_sys	mini;

	signal(SIGINT, handler);	// sort out how to do sigaction instead
	if (!init_sys(&mini, env))
		return (127); 			// Message d'erreur a definir en cas de non initialisation
	line = NULL;
	if (ac != 1 || av[0][1] == '1')
		return (0);
	while (1)
	{
		line = readline("$> ");
		add_history(line);
		if (!parse(line, &mini))
		{
			// besoin d'une fonction de free complet de tout la strucutre t_sys et 
			// des structures et listes internes
			// une fois que tout est free on peut continue
		}
		exec(mini.cmds, &mini);
		// besoin d'une fonction de free complet de tout la strucutre t_sys et 
		// des structures et listes internes
		// une fois que tout est free on peut continue
	}
	return (0);
}
