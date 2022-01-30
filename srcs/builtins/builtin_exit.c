/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:19:25 by pravry            #+#    #+#             */
/*   Updated: 2022/01/30 16:25:26 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **args, t_sys *mini)
{
	mini->exit = 1;
	if (args[1] && args[2])
	{
		mini->retval = 1;
		ft_putstr_fd("minishell : exit: too many arguments", STDERR_FILENO);
	}
	else if (args[1] && ft_strisnum(args[1]) == 0)
	{
		mini->retval = 255;
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	else if (args[1])
		mini->retval = ft_atoi(args[1]);
	else
		mini->retval = 0;
}
