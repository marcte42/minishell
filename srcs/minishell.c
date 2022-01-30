/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:55:02 by pravry            #+#    #+#             */
/*   Updated: 2022/01/30 13:37:29 by mterkhoy         ###   ########.fr       */
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
	//g_var.status += sig;

// Don't use printf in signal handlers

//	ft_putstr_fd("\nthe handler value: ", 2);
//	ft_putnbrnl_fd(sig, 2);

	if (sig == SIGINT)
	{	// control_c
//		ft_putstr("we should be in sigint\n");
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
	//	rl_replace_line("", 0);	// doesn't exit in mac -lreadline library...
		rl_redisplay();
		g_var.status = 130;
		g_var.signal = 1;
/*
		ft_putchar_fd('\n', 2);
		if (g_var.pid == 0)
		{
			prompt();
		}
		g_var.status = 130;
		g_var.signal = 1;
*/
	}
/*	else if (sig == SIGQUIT)
	{	// control_slash
		ft_putstr("we should be in sigquit\n");
		g_var.signal = 2;
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		exit(1);
	}
*/
}

int	main(int ac, char **av, char *env[])
{
	char	*line;
	t_sys	mini;
	// struct sigaction    s1;

	//g_sig_exit = -1;

	// s1.sa_handler = &signal_handler;
	// sigaction(SIGINT, &s1, NULL);
	// I'm an idiot, you can't do a Sigaction on Sigquit, or is it Sigterm it doesn't work on...
	// either way doesn't really matter have a better way of dealing with it...
//	sigaction(SIGQUIT, &s1, NULL);
//	signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, handler);	// sort out how to do sigaction instead
	if (!init_sys(&mini, env))
		return (127); 			// Message d'erreur a definir en cas de non initialisation
	line = NULL;
	if (ac != 1 || av[0][1] == '1')
		return (0);
	while (1)
	{
		// this did not help, prolly get rid of it
//		sigaction(SIGINT, &s1, NULL);
//		sigaction(SIGQUIT, &s1, NULL);
//		signal(SIGQUIT, SIG_IGN);
		line = readline("$> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			return (0);
		}
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
