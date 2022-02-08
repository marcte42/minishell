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

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
		rl_replace_line("", 0);	// doesn't exit in mac -lreadline library...
		rl_redisplay();
	}
}

void	signal_handler_2(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
	//	free_from_signal(NULL);
	//	exit(130);				// not sure this method is gonna work for us...
	}
	else if (sig == SIGQUIT)
	{
	//	printf("\r");
		ft_putstr_fd("\r", 2);
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \r", 2);
	//	printf("  ");
	//	printf("\r");
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int ac, char **av, char *env[])
{
	t_sys	mini;
	(void)	av;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!init_sys(&mini, env))
		return (127);
	if (ac != 1)
		return (0);
	while (1)
	{
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
