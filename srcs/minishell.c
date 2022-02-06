/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:55:02 by pravry            #+#    #+#             */
/*   Updated: 2022/02/06 13:41:30 by mterkhoy         ###   ########.fr       */
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
		rl_replace_line("", 0);	// doesn't exit in mac -lreadline library...
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

void	signal_handler_2(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		g_var.status = 130;

/*
		rl_on_new_line();
		rl_replace_line("", 0);
*/
// not sure which is better
	// The second one works, the first does not...
		rl_replace_line("", 0);
		rl_redisplay();

	}
}

int	main(int ac, char **av, char *env[])
{
	t_sys	mini;

	signal(SIGINT, signal_handler);	// sort out how to do sigaction instead
	// not clear if i also need to handle SIGQUIT...
	signal(SIGQUIT, SIG_IGN);
	if (!init_sys(&mini, env))
		return (127); 			// Message d'erreur a definir en cas de non initialisation
	if (ac != 1 || av[0][1] == '1')
		return (0);
	while (1)
	{
		// this did not help, prolly get rid of it
//		sigaction(SIGINT, &s1, NULL);
//		sigaction(SIGQUIT, &s1, NULL);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		mini.line = readline("$> ");
		if (!mini.line)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		if (!*(mini.line))
		{
			free(mini.line);
			continue ;
		}
		add_history(mini.line);
		parse(&mini);
		exec(&mini);
		if (mini.exit)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_lstclear(&mini.env, free);
			free_sys(&mini);
			return (mini.retval);
		}	
		free_sys(&mini);		
	//	ft_putstr_fd("made it to end of main loop\n", 1);
	//	ft_env(&mini, 1);
		
	}
	// free_sys(&mini); // put this here? would that even do anything?
	//where exactly do we exit and where does that value get returned?
	// should we change the conditions of the loop to exit when certain exit status are returned?
	ft_lstclear(&mini.env, free);
	// works cuz break
	// also need to clear_history()
	return (0);
}
