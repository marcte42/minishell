/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:19:25 by pravry            #+#    #+#             */
/*   Updated: 2021/07/01 11:21:06 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **args, t_sys *mini)
{
	mini->exit = 1;
	if (args[1] && args[2])
	{
		mini->ret = 1;
		ft_putstr_fd("minishell : exit: too many arguments", STDERR);
	}
	else if (args[1] && ft_strisnum(args[1]) == 0)
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (args[1])
		mini->ret = ft_atoi(args[1]);
	else
		mini->ret = 0;
}
