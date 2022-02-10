/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:55:02 by pravry            #+#    #+#             */
/*   Updated: 2022/02/10 20:49:21 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*g_ptr;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		*g_ptr = 130;
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_2(int sig)
{
	if (sig == SIGINT)
	{
		*g_ptr = 130;
		ft_putchar_fd('\n', 2);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	more_main(t_sys *mini)
{
	if (!*(mini->line))
	{
		rl_redisplay();
		free_sys(mini);
		return (1);
	}
	add_history(mini->line);
	if (!parse(mini))
	{
		mini->retval = 2;
		free_sys(mini);
		return (1);
	}
	mini->retval = exec(mini);
	if (mini->exit)
	{
		ft_lstclear(&mini->env, free);
		free_sys(mini);
		rl_clear_history();
		return (0);
	}
	free_sys(mini);
	return (1);
}

int	main(int ac, char **av, char *env[])
{
	t_sys	mini;

	(void)av;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!init_sys(&mini, env))
		return (127);
	g_ptr = &mini.retval;
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
		if (!more_main(&mini))
			return (mini.retval);
	}
	ft_lstclear(&mini.env, free);
	rl_clear_history();
	return (0);
}
