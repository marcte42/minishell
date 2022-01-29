/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:55:02 by pravry            #+#    #+#             */
/*   Updated: 2022/01/29 17:35:13 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// temporarily using a simple global var, just an int
	// actually it's way more complicated, might as well just use a structure


t_var	g_var;


/*void handler(int sig)
{
	if (sig == SIGINT)
		rl_redisplay();
	exit(0);
}
*/

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{	// control_c

		
	}
	else if (sig == SIGQUIT)
	{	// control_slash


	}
	
}



int	main(int ac, char **av, char *env[])
{
	char	*line;
	t_sys	mini;
	struct sigaction    s1;

	g_sig_exit = -1;

	s1.sa_handler = &handler;
	sigaction(SIGINT, &s1, NULL);
	//signal(SIGINT, handler);	// sort out how to do sigaction instead
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
			// besoin d'une fonction de free complet de toute la strucuture t_sys et 
			// des structures et listes internes
			// une fois que tout est free on peut continue
		}
		exec(mini.cmds, &mini);
		// besoin d'une fonction de free complet de toute la structure t_sys et 
		// des structures et listes internes
		// une fois que tout est free on peut continue
		free(line);
	}
	return (0);
}
