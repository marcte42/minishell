/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:55:02 by pravry            #+#    #+#             */
/*   Updated: 2022/02/07 22:31:47 by mterkhoy         ###   ########.fr       */
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
	(void)	av;

	// for a tester
	// ahhh no, we should prolly implement this anyway... it's the thing that lets us run in non interactive mode...
/*
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
  	{
		int exit_status = ft_launch_minishell(av[2]);
		exit(exit_status);
 	}
*/

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!init_sys(&mini, env))
		return (127);
	if (ac != 1)
		return (0);
	while (1)
	{
//		signal(SIGINT, signal_handler);
//		signal(SIGQUIT, SIG_IGN);
		mini.line = readline("$> ");
		if (!mini.line)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			free_sys(&mini);
			break ;
		}
		if (!*(mini.line))
		{
			free_sys(&mini);
			continue ;
		}
		add_history(mini.line);
		if (!parse(&mini))
		{
			mini.retval = 2;
			free_sys(&mini);
			continue ;
		}
		mini.retval = exec(&mini);
		if (mini.exit)
		{
			ft_lstclear(&mini.env, free);
			free_sys(&mini);
			return (mini.retval);
		}
		free_sys(&mini);
	}
	ft_lstclear(&mini.env, free);
	return (0);
}
